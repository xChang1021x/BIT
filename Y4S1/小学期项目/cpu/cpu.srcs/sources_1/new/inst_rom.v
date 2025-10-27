`include "defines.v"
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2025/08/31 00:01:27
// Design Name: 
// Module Name: inst_rom
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


module inst_rom(
        input wire                  ce,
        input wire[`InstAddrBus]    addr,
        output reg[`InstBus]        inst
    );
    
    reg[`InstBus]   inst_mem[0:`InstMemNum-1];
    
    initial begin
        $readmemh ("D:/xChangx/University/BIT/Y4S1/LAB/cpu-git/cpu/cpu.srcs/sources_1/new/inst_rom.txt", inst_mem);
        $display("%h", inst_mem[0]);
        $display("%h", inst_mem[1]);
        $display("%h", inst_mem[2]);
        $display("%h", inst_mem[3]);
    end
    
    always @ (*) begin
        if (ce == `ChipDisable) begin
            inst <= `ZeroWord;
        end else begin
            inst <= inst_mem[addr[`InstMemNumLog2+1:2]];
        end    
    end     
                
endmodule
