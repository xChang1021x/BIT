`timescale 1ns / 1ps

module time_counter(
    input clk,              // 系统时钟
    input pause_key,        // 暂停按键
    input reset_key,        // 复位按键
    input start_key,        // 开始计时按键
    output reg [7:0] sig_seg,   // 段选
    output reg [3:0] CS,        // 位选信号
    output reg light,       // LED灯
    output reg alert        // 蜂鸣器
);

    reg [1:0] min;          // 分钟
    reg started;            // 1表示正在计时，0表示暂停
    reg temp;               // 1/0表示时钟信号的继续或暂停状态
    reg [16:0] ctr1;    
    reg [16:0] ctr0;        // 自定义时钟计数器，每1ms循环一次
    reg [1:0] ctr2;      
    reg [3:0] ms;           // 毫秒个位
    reg [3:0] tms;          // 毫秒十位
    reg [3:0] hms;          // 毫秒百位
    reg [3:0] s;            // 秒个位
    reg [3:0] ts;           // 秒十位

    reg [16:0] count_end = 17'd50618; // 蜂鸣器频率 表示7
    reg [16:0] ctr_beep;    // 蜂鸣器计数器

    // Initialize registers
    initial begin
        min = 2'b00;
        started = 1'b0;
        temp = 1'b1;
        sig_seg = 8'b0000_0000;
        CS = 4'b1000;
        light = 1'b0;
        alert = 1'b0;
        ctr1 = 17'd0;
        ctr0 = 17'd0;
        ctr2 = 2'd0;
        ms = 4'd0;
        tms = 4'd0;
        hms = 4'd0;
        s = 4'd0;
        ts = 4'd0;
        ctr_beep = 17'd0;
    end

    // Main clocked process
    always @(posedge clk or negedge reset_key) begin
        if (!reset_key) begin
            // Reset all registers
            started <= 1'b0;
            ctr1 <= 17'd0;
            ctr2 <= 2'd0;
            ms <= 4'd0;
            tms <= 4'd0;
            hms <= 4'd0;
            s <= 4'd0;
            ts <= 4'd0;
            min <= 2'b00;
            light <= 1'b0;
            temp <= 1'b1;
            alert <= 1'b0;
            ctr_beep <= 17'd0;
        end
        else begin
            // Handle start/pause keys synchronously
            if (start_key) started <= 1'b1;
            if (pause_key) started <= 1'b0;
            
            // Increment counters
            ctr_beep <= ctr_beep + 1'b1;
            ctr0 <= (ctr0 == 17'd10_0000) ? 17'd1 : ctr0 + 1;
            
            // Handle beep
            if (ctr_beep == count_end) begin
                ctr_beep <= 17'd0;
                if (temp == 1'b0) alert <= !alert;
            end
            
            // Handle timing logic
            if (started) begin
                if (ctr1 == 17'd10_0000) begin
                    ctr1 <= 17'd1;
                    ms <= ms + temp;
                    
                    // Cascade counters
                    if (ms == 4'd9) begin
                        ms <= 4'd0;
                        tms <= tms + 1;
                        
                        if (tms == 4'd9) begin
                            tms <= 4'd0;
                            hms <= hms + 1;
                            
                            if (hms == 4'd9) begin
                                hms <= 4'd0;
                                s <= s + 1;
                                
                                if (s == 4'd9) begin
                                    s <= 4'd0;
                                    ts <= ts + 1;
                                    
                                    if (ts == 4'd5 && min == 2'b00) begin
                                        min <= 2'b01;
                                        light <= 1'b1;
                                        ms <= 4'd0;
                                        tms <= 4'd0;
                                        hms <= 4'd0;
                                        s <= 4'd0;
                                        ts <= 4'd0;
                                    end
                                    
                                    if (ts == 4'd5 && min == 2'b01) begin
                                        temp <= 1'b0;
                                    end
                                end
                            end
                        end
                    end
                end
                else begin
                    ctr1 <= ctr1 + 1;
                end
            end
            
            // Handle digit selection
            ctr2 <= (ctr0 == 17'd10_0000) ? ((ctr2 == 2'd3) ? 2'd0 : ctr2 + 1) : ctr2;
            
            // Display logic
            case (ctr2)
                2'd0: begin
                    CS <= 4'b1000;
                    case(ts)
                        4'd0: sig_seg <= 8'b0111_1110;
                        4'd1: sig_seg <= 8'b0000_1100;           
                        4'd2: sig_seg <= 8'b1011_0110;           
                        4'd3: sig_seg <= 8'b1001_1110;      
                        4'd4: sig_seg <= 8'b1100_1100;          
                        4'd5: sig_seg <= 8'b1101_1010;       
                        4'd6: sig_seg <= 8'b1111_1010;       
                        4'd7: sig_seg <= 8'b0000_1110; 
                        4'd8: sig_seg <= 8'b1111_1110;  
                        4'd9: sig_seg <= 8'b1101_1110;
                        default:;
                    endcase
                end
                // ... (other digit cases)
                2'd1: begin      
                    CS <= 4'b0100;
                    case(s)
                        4'd0:sig_seg <= 8'b0111_1111;
                        4'd1:sig_seg <= 8'b0000_1101;
                        4'd2:sig_seg <= 8'b1011_0111;
                        4'd3:sig_seg <= 8'b1001_1111;
                        4'd4:sig_seg <= 8'b1100_1101;
                        4'd5:sig_seg <= 8'b1101_1011;
                        4'd6:sig_seg <= 8'b1111_1011;
                        4'd7:sig_seg <= 8'b0000_1111;
                        4'd8:sig_seg <= 8'b1111_1111;
                        4'd9:sig_seg <= 8'b1101_1111;
                        default:;
                    endcase
                end
                2'd2:begin      
                    CS <= 4'b0010;
                    case(hms)
                        4'd0:sig_seg <= 8'b0111_1110;
                        4'd1:sig_seg <= 8'b0000_1100;
                        4'd2:sig_seg <= 8'b1011_0110;
                        4'd3:sig_seg <= 8'b1001_1110;
                        4'd4:sig_seg <= 8'b1100_1100;
                        4'd5:sig_seg <= 8'b1101_1010;
                        4'd6:sig_seg <= 8'b1111_1010;
                        4'd7:sig_seg <= 8'b0000_1110;
                        4'd8:sig_seg <= 8'b1111_1110;
                        4'd9:sig_seg <= 8'b1101_1110;
                        default:;
                    endcase
                end
                2'd3:begin   
                    CS <= 4'b0001;
                    case(tms)
                        4'd0:sig_seg <= 8'b0111_1110;
                        4'd1:sig_seg <= 8'b0000_1100;
                        4'd2:sig_seg <= 8'b1011_0110;
                        4'd3:sig_seg <= 8'b1001_1110;
                        4'd4:sig_seg <= 8'b1100_1100;
                        4'd5:sig_seg <= 8'b1101_1010;
                        4'd6:sig_seg <= 8'b1111_1010;
                        4'd7:sig_seg <= 8'b0000_1110;
                        4'd8:sig_seg <= 8'b1111_1110;
                        4'd9:sig_seg <= 8'b1101_1110;
                        default:;
                    endcase
                end
                default:;
            endcase
        end
    end

endmodule