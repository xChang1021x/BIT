`include "defines.v"
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2025/08/29 20:10:16
// Design Name: 
// Module Name: pc_reg
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


module pc_reg(
        input wire                  clk,
        input wire                  rst,
        input wire                  branch_flag_i,
        input wire[`InstAddrBus]    branch_target_i,
        input wire                  jump_flag_i,
        input wire[`InstAddrBus]    jump_target_i,
        output reg[`InstAddrBus]    pc,
        output reg                  ce
    );
    
    always @ (posedge clk) begin
        if (rst == `RstEnable) begin
            ce <= `ChipDisable;
        end else begin
            ce <= `ChipEnable;
        end
    end 
    
    always @ (posedge clk) begin
        if (ce == `ChipDisable) begin
            pc <= 32'h00000000;
        end else if (jump_flag_i == `JumpEnable) begin // 跳转优先级最高
            pc <= jump_target_i;
        end else if (branch_flag_i == `BranchEnable) begin // 其次是分支
            pc <= branch_target_i;
        end else begin
            pc <= pc + 4'h4;
        end
   end 
endmodule
