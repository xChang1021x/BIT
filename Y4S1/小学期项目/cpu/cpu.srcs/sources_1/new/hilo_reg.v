`include "defines.v"
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/02/2025 01:38:11 PM
// Design Name: 
// Module Name: hilo_reg
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


module hilo_reg(
    input wire  clk,
    input wire  rst,
    
    input wire we,
    input wire[`RegBus] hi_i,
    input wire[`RegBus] lo_i,
    
    output reg[`RegBus] hi_o,
    output reg[`RegBus] lo_o
    );
    
    always @ (posedge clk) begin
        if(rst == `RstEnable) begin
            hi_o <= `ZeroWord;
            lo_o <= `ZeroWord;
        end else if((we == `WriteEnable)) begin
            hi_o <= hi_i;
            lo_o <= lo_i;
        end
    end
endmodule
