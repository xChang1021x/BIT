`timescale 1ns / 1ps

module testbench(

    );
    reg clk;
    reg rst_n;
    reg in;
    wire out;
    always #5 clk<=~clk;
    
    initial begin
        clk <= 'b0;
        rst_n <= 'b0;
        in <= 'b1;
        #5 rst_n <= 'b1;
       
       //输入01
       #10 in <= 'b0;
       #10 in <= 'b1;
       
       //输入001
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b1;
       
       //输入0001
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b1;
       
       //输入00001
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b1;
       
       //输入000001
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b0;
       #10 in <= 'b1;
        
    end
    
    Exp2 exp2(
        .clk (clk ),
        .rst_n (rst_n),
        .in (in ),
        .out (out )
    );
endmodule
