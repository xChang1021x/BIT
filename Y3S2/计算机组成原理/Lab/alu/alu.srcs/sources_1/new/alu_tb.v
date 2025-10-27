`timescale 1ns/1ps

module ALU_tb;

    // 输入信号
    reg [31:0] A;
    reg [31:0] B;
    reg [2:0] ALU_Control;
    reg Round_Mode;
    
    // 输出信号
    wire [31:0] Result;
    wire SF, CF, ZF, OF, PF;
    
    // 实例化被测ALU
    ALU_32bit uut (
        .A(A),
        .B(B),
        .ALU_Control(ALU_Control),
        .Round_Mode(Round_Mode),
        .Result(Result),
        .SF(SF),
        .CF(CF),
        .ZF(ZF),
        .OF(OF),
        .PF(PF)
    );
    
    // 测试过程
    initial begin
        // 初始化输入
        A = 0;
        B = 0;
        ALU_Control = 0;
        Round_Mode = 0;
        
        // 波形记录
        $dumpfile("alu_wave.vcd");
        $dumpvars(0, ALU_tb);
        
        $display("=== 开始32位ALU测试 ===");
        
        // 测试1: 算术运算
        $display("\n[测试1] 算术运算测试");
        ALU_Control = 3'b000; // 加法
        
        // 正常加法
        A = 32'd5; B = 32'd3; #10;
        $display("5 + 3 = %d (ZF=%b, CF=%b, OF=%b)", Result, ZF, CF, OF);
        
        // 溢出测试(正溢出)
        A = 32'h7FFFFFFF; B = 32'd1; #10;
        $display("MAX_INT + 1 = %h (OF=%b)", Result, OF);
        
        // 溢出测试(负溢出)
        A = 32'h80000000; B = 32'hFFFFFFFF; #10;
        $display("MIN_INT - 1 = %h (OF=%b)", Result, OF);
        
        // 测试2: 减法
        $display("\n[测试2] 减法测试");
        ALU_Control = 3'b001; // 减法
        A = 32'd10; B = 32'd4; #10;
        $display("10 - 4 = %d (CF=%b)", Result, CF);
        
        // 借位测试
        A = 32'd0; B = 32'd1; #10;
        $display("0 - 1 = %h (CF=%b)", Result, CF);
        
        // 测试3: 逻辑运算
        $display("\n[测试3] 逻辑运算测试");
        A = 32'hF0F0F0F0; B = 32'h0F0F0F0F;
        
        ALU_Control = 3'b010; #10; // 与运算
        $display("F0F0F0F0 AND 0F0F0F0F = %h", Result);
        
        ALU_Control = 3'b011; #10; // 或运算
        $display("F0F0F0F0 OR 0F0F0F0F = %h", Result);
        
        ALU_Control = 3'b100; #10; // 异或运算
        $display("F0F0F0F0 XOR 0F0F0F0F = %h", Result);
        
        // 测试4: 移位运算
        $display("\n[测试4] 移位运算测试");
        A = 32'h0000000F; B = 32'd4;
        
        ALU_Control = 3'b101; #10; // 逻辑左移
        $display("0x0000000F << 4 = %h", Result);
        
        A = 32'hF0000000;
        ALU_Control = 3'b110; #10; // 逻辑右移
        $display("0xF0000000 >> 4 = %h", Result);
        
        ALU_Control = 3'b111; #10; // 算术右移
        $display("0xF0000000 >>> 4 = %h", Result);
        
        // 测试5: 标志位专项测试
        $display("\n[测试5] 标志位测试");
        
        // 零标志测试
        ALU_Control = 3'b000; // 加法
        A = 0; B = 0; #10;
        $display("0 + 0 = %h (ZF=%b)", Result, ZF);
        
        // 符号标志测试
        A = 32'h80000000; B = 32'd1; #10;
        $display("MIN_INT + 1 = %h (SF=%b)", Result, SF);
        
        // 奇偶标志测试
        A = 32'd3; B = 32'd0; #10;
        $display("3 + 0 = %h (PF=%b)", Result, PF);
        
        // 测试完成
        $display("\n=== 所有测试完成 ===");
        #100 $finish;
    end
    
endmodule