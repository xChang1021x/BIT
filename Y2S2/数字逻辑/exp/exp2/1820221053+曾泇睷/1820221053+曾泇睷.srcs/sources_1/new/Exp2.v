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
//��λ��ص�Ĭ��̬
    if(~rst_n) begin
        current_state <= STATE_IDLE;
    end
    else begin
        current_state <= next_state;
    end
end

always @(*) begin
    case (current_state)
        //ֻҪ����0�ͽ�����һ״̬
        STATE_IDLE: next_state = (in=='b0) ? STATE_S1 : STATE_IDLE;     //IDLE״̬
        STATE_S1 : next_state = (in=='b0) ? STATE_S2 : STATE_IDLE;      //S1״̬
        STATE_S2 : next_state = (in=='b0) ? STATE_S3 : STATE_IDLE;      //S2״̬
        STATE_S3 : next_state = (in=='b0) ? STATE_S4 : STATE_IDLE;      //S3״̬
        //�Ѿ�����������4��0���룬��������0��Ȼͣ��
        STATE_S4 : next_state = (in=='b0) ? STATE_S4 : STATE_IDLE;      //S4״̬
        default:
        next_state = STATE_IDLE;
    endcase
end

always @ (posedge clk or negedge rst_n) begin
    #clk
    if(~rst_n) begin
    out <= 'b0;
    end
    //״̬�ﵽS4�����1������õ�Ŀ��������
    else if(current_state==STATE_S4) begin
    out <= 'b1;
    end
    //û�дﵽ״̬S4�����0������û�еõ�Ŀ��������
    else begin
    out <= 'b0;
    end
end
endmodule
