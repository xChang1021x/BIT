`include "defines.v"

module if_id(
    input wire  clk,
    input wire rst,
    
    input wire                  flush_i,
    input wire[`InstAddrBus]    if_pc,
    input wire[`InstBus]        if_inst,
    
    output reg[`InstAddrBus]    id_pc,
    output reg[`InstBus]        id_inst
    
);


    always @ (posedge clk) begin
        if (rst == `RstEnable) begin
            id_pc <= `ZeroWord;
            id_inst <= `ZeroWord;
        end else if (flush_i == `FlushEnable) begin // 如果收到冲刷信号
            id_pc <= `ZeroWord;
            id_inst <= `ZeroWord; // 将指令清零 -> 相当于插入nop
        end else begin
            id_pc <= if_pc;
            id_inst <= if_inst;
        end
    end     
endmodule
