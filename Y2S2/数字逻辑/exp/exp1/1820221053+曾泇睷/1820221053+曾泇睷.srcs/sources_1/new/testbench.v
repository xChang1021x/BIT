`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/06/11 13:35:18
// Design Name: 
// Module Name: square
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module testbench(

    );
    reg A, B, C;
    wire[5:0] value;
    
    initial begin
        A = 1'b0;
        #20 A = 1'b1;
    end 
    
    initial begin
        B = 1'b0;
        #10 B = 1'b1;
        #10 B = 1'b0;
        #10 B = 1'b1;
    end
    
    initial begin
        C = 1'b0;
        #5 C = 1'b1;  
        #5 C = 1'b0;
        #5 C = 1'b1;
        #5 C = 1'b0;
        #5 C = 1'b1;
        #5 C = 1'b0;
        #5 C = 1'b1;  
     end
     
    square square(
        .a(A),
        .b(B),
        .c(C),
        .value(value)
     );
endmodule
