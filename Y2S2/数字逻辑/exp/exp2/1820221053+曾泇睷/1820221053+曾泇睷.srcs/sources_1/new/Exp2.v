`timescale 1ns / 1ps

module Exp2(
    input clk,
    input rst_n,
    input in,
    output reg out
    );
    
parameter STATE_IDLE = 4'b0;
parameter STATE_S1 = 4'b0001;
parameter STATE_S2 = 4'b0010;
parameter STATE_S3 = 4'b0011;
parameter STATE_S4 = 4'b0100;

reg [3:0] current_state;
reg [3:0] next_state;

always @ (posedge clk or negedge rst_n) begin
//复位则回到默认态
    if(~rst_n) begin
        current_state <= STATE_IDLE;
    end
    else begin
        current_state <= next_state;
    end
end

always @(*) begin
    case (current_state)
        //只要输入0就进入下一状态
        STATE_IDLE: next_state = (in=='b0) ? STATE_S1 : STATE_IDLE;     //IDLE状态
        STATE_S1 : next_state = (in=='b0) ? STATE_S2 : STATE_IDLE;      //S1状态
        STATE_S2 : next_state = (in=='b0) ? STATE_S3 : STATE_IDLE;      //S2状态
        STATE_S3 : next_state = (in=='b0) ? STATE_S4 : STATE_IDLE;      //S3状态
        //已经检测出来连续4个0输入，继续输入0仍然停在
        STATE_S4 : next_state = (in=='b0) ? STATE_S4 : STATE_IDLE;      //S4状态
        default:
        next_state = STATE_IDLE;
    endcase
end

always @ (posedge clk or negedge rst_n) begin
    #clk
    if(~rst_n) begin
    out <= 'b0;
    end
    //状态达到S4，输出1，代表得到目标子序列
    else if(current_state==STATE_S4) begin
    out <= 'b1;
    end
    //没有达到状态S4，输出0，代表没有得到目标子序列
    else begin
    out <= 'b0;
    end
end
endmodule
