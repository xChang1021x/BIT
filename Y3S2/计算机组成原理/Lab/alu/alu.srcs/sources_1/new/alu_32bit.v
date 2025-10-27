`timescale 1ns/1ps

module ALU_32bit (
    input [31:0] A,           // 输入操作数A
    input [31:0] B,           // 输入操作数B
    input [2:0] ALU_Control,  // ALU操作控制信号
    input Round_Mode,         // 舍入模式选择(0:向零舍入,1:四舍五入)
    output reg [31:0] Result, // 运算结果
    output reg SF,            // 符号标志（改为reg类型）
    output reg CF,            // 进位标志（改为reg类型）
    output reg ZF,            // 零标志（改为reg类型）
    output reg OF,            // 溢出标志（改为reg类型）
    output reg PF             // 奇偶标志（改为reg类型）
);

    // 内部信号
    wire [32:0] add_result;   // 加法结果（33位包含进位）
    wire [32:0] sub_result;   // 减法结果（33位包含借位）
    reg [31:0] rounded_result; // 舍入后结果
    
    // 运算逻辑
    always @(*) begin
        case(ALU_Control)
            3'b000: begin // 加法
                {CF, Result} = A + B;
                OF = (A[31] == B[31]) && (Result[31] != A[31]);
                SF = Result[31];
                ZF = (Result == 32'b0);
                PF = ~^Result[7:0];
            end
            3'b001: begin // 减法
                {CF, Result} = A - B;
                OF = (A[31] != B[31]) && (Result[31] != A[31]);
                SF = Result[31];
                ZF = (Result == 32'b0);
                PF = ~^Result[7:0];
            end
            3'b010: begin // 按位与
                Result = A & B;
                CF = 0; OF = 0;
                SF = Result[31];
                ZF = (Result == 32'b0);
                PF = ~^Result[7:0];
            end
            3'b011: begin // 按位或
                Result = A | B;
                CF = 0; OF = 0;
                SF = Result[31];
                ZF = (Result == 32'b0);
                PF = ~^Result[7:0];
            end
            3'b100: begin // 按位异或
                Result = A ^ B;
                CF = 0; OF = 0;
                SF = Result[31];
                ZF = (Result == 32'b0);
                PF = ~^Result[7:0];
            end
            3'b101: begin // 逻辑左移
                Result = A << B[4:0];
                CF = 0; OF = 0;
                SF = Result[31];
                ZF = (Result == 32'b0);
                PF = ~^Result[7:0];
            end
            3'b110: begin // 逻辑右移
                Result = A >> B[4:0];
                CF = 0; OF = 0;
                SF = Result[31];
                ZF = (Result == 32'b0);
                PF = ~^Result[7:0];
            end
            3'b111: begin // 算术右移
                Result = $signed(A) >>> B[4:0];
                CF = 0; OF = 0;
                SF = Result[31];
                ZF = (Result == 32'b0);
                PF = ~^Result[7:0];
            end
            default: begin
                Result = 32'b0;
                CF = 0; OF = 0;
                SF = 0;
                ZF = 1;
                PF = 1;
            end
        endcase
        
        // 舍入处理（简单示例）
        if (Round_Mode == 1'b0) begin
            rounded_result = Result; // 实际应向零舍入
        end else begin
            rounded_result = Result + (Result[0] & (|Result[31:1])); // 四舍五入
        end
    end

endmodule