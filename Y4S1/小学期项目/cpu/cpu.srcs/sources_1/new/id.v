`include "defines.v"

module id(
    input wire                  rst,
    input wire[`InstAddrBus]    pc_i,
    input wire[`InstBus]        inst_i,
    
    input wire[`RegBus]         reg1_data_i,
    input wire[`RegBus]         reg2_data_i,
    
    input wire                  ex_wreg_i,
    input wire[`RegBus]         ex_wdata_i,
    input wire[`RegAddrBus]     ex_wd_i,
    
    input wire                  mem_wreg_i,
    input wire[`RegBus]         mem_wdata_i,
    input wire[`RegAddrBus]     mem_wd_i,
    
    output reg                  reg1_read_o,
    output reg                  reg2_read_o,
    output reg[`RegAddrBus]     reg1_addr_o,
    output reg[`RegAddrBus]     reg2_addr_o,
    
    //传递到执行阶段的信息
    output reg[`AluOpBus]       aluop_o,
    output reg[`AluSelBus]      alusel_o,
    output reg[`RegBus]         reg1_o,
    output reg[`RegBus]         reg2_o,
    output reg[`RegAddrBus]     wd_o,
    output reg                  wreg_o,
    
    output reg                  branch_flag_o,
    output reg[`InstAddrBus]    branch_target_o,
    output reg                  jump_flag_o,
    output reg[`InstAddrBus]    jump_target_o,
    output reg                  flush_o // 冲刷信号
);

wire[5:0] op = inst_i[31:26];  // 指令码
wire[4:0] op2 = inst_i[10:6];
wire[5:0] op3 = inst_i[5:0];  // 功能码
wire[4:0] op4 = inst_i[20:16];

reg[`RegBus]    imm;

reg instvalid;

    always@(*) begin
        if(rst == `RstEnable) begin
            aluop_o <= `EXE_NOP_OP;
            alusel_o <= `EXE_RES_NOP;
            wd_o <= `NOPRegAddr;
            wreg_o <= `WriteDisable;
            instvalid <= `InstValid;
            reg1_read_o <= 1'b0;
            reg2_read_o <= 1'b0;
            reg1_addr_o <= `NOPRegAddr;
            reg2_addr_o <= `NOPRegAddr;
            imm <= 32'h0;
            branch_flag_o <= `ZeroWord;
            branch_target_o <= `ZeroWord;
            jump_flag_o <= `ZeroWord;
            jump_target_o <= `ZeroWord;
            flush_o <= `FlushDisable;
        end else begin
            aluop_o <= `EXE_NOP_OP;
            alusel_o <= `EXE_RES_NOP;
            wd_o <= inst_i[15:11];
            wreg_o <= `WriteDisable;
            instvalid <= `InstInvalid;
            reg1_read_o <= 1'b0;
            reg2_read_o <= 1'b0;
            reg1_addr_o <= inst_i[25:21];
            reg2_addr_o <= inst_i[20:16];
            imm <= `ZeroWord;
            branch_flag_o <= `ZeroWord;
            branch_target_o <= `ZeroWord;
            jump_flag_o <= `ZeroWord;
            jump_target_o <= `ZeroWord;
            flush_o <= `FlushDisable;
            
            case (op)
                `EXE_SPECIAL_INST: begin  // 指令码是 SPECIAL
                    case (op2)
                        5'b00000: begin
                            case(op3)  // 依据功能码进行判断
                                `EXE_OR: begin  // or 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_OR_OP;
                                    alusel_o    <= `EXE_RES_LOGIC;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_AND: begin  // and 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_AND_OP;
                                    alusel_o    <= `EXE_RES_LOGIC;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_XOR: begin  // xor 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_XOR_OP;
                                    alusel_o    <= `EXE_RES_LOGIC;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_NOR: begin  // nor 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_NOR_OP;
                                    alusel_o    <= `EXE_RES_LOGIC;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_SLLV: begin  // sllv 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_SLL_OP;
                                    alusel_o    <= `EXE_RES_SHIFT;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_SRLV: begin  // srlv 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_SRL_OP;
                                    alusel_o    <= `EXE_RES_SHIFT;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_SRAV: begin  // srav 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_SRA_OP;
                                    alusel_o    <= `EXE_RES_SHIFT;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_SYNC: begin  // sync 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_NOP_OP;
                                    alusel_o    <= `EXE_RES_NOP;
                                    reg1_read_o <= 1'b0;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                end
                                // 移动指令
                                `EXE_MFHI: begin  // mfhi 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_MFHI_OP;
                                    alusel_o    <= `EXE_RES_MOVE;
                                    reg1_read_o <= 1'b0;
                                    reg2_read_o <= 1'b0;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_MFLO: begin  // mflo 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_MFLO_OP;
                                    alusel_o    <= `EXE_RES_MOVE;
                                    reg1_read_o <= 1'b0;
                                    reg2_read_o <= 1'b0;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_MTHI: begin  // mthi 指令
                                    wreg_o      <= `WriteDisable;
                                    aluop_o     <= `EXE_MTHI_OP;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b0;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_MTLO: begin  // mtlo 指令
                                    wreg_o      <= `WriteDisable;
                                    aluop_o     <= `EXE_MTLO_OP;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b0;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_MOVN: begin  // movn 指令
                                    aluop_o     <= `EXE_MOVN_OP;
                                    alusel_o    <= `EXE_RES_MOVE;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                    if(reg2_o != `ZeroWord) begin
                                        wreg_o <= `WriteEnable;
                                    end else begin
                                        wreg_o <= `WriteDisable;
                                    end
                                end
                                `EXE_SLT: begin  // slt 指令
                                    wreg_o      <= `WriteEnable;
                                    aluop_o     <= `EXE_SLT_OP;
                                    reg1_read_o <= 1'b1;
                                    reg2_read_o <= 1'b1;
                                    instvalid   <= `InstValid;
                                end
                                `EXE_SLTU: begin  // sltu 指令
                                    wreg_o       <= `WriteEnable;
                                    aluop_o      <= `EXE_SLTU_OP;
                                    alusel_o     <= `EXE_RES_ARITHMETIC;
                                    reg1_read_o  <= 1'b1;
                                    reg2_read_o  <= 1'b1;
                                    instvalid    <= `InstValid;
                                end
                                `EXE_ADD: begin  // add 指令                                  // add指令
                                    wreg_o       <= `WriteEnable;
                                    aluop_o      <= `EXE_ADD_OP;
                                    alusel_o     <= `EXE_RES_ARITHMETIC;
                                    reg1_read_o  <= 1'b1;
                                    reg2_read_o  <= 1'b1;
                                    instvalid    <= `InstValid;
                                end
                                `EXE_ADDU: begin  // addu 指令
                                    wreg_o       <= `WriteEnable;
                                    aluop_o      <= `EXE_ADDU_OP;
                                    alusel_o     <= `EXE_RES_ARITHMETIC;
                                    reg1_read_o  <= 1'b1;
                                    reg2_read_o  <= 1'b1;
                                    instvalid    <= `InstValid;
                                end
                                `EXE_SUB: begin  // sub 指令
                                    wreg_o       <= `WriteEnable;
                                    aluop_o      <= `EXE_SUB_OP;
                                    alusel_o     <= `EXE_RES_ARITHMETIC;
                                    reg1_read_o  <= 1'b1;
                                    reg2_read_o  <= 1'b1;
                                    instvalid    <= `InstValid;
                                end
                                `EXE_SUBU: begin  // subu 指令
                                    wreg_o       <= `WriteEnable;
                                    aluop_o      <= `EXE_SUBU_OP;
                                    alusel_o     <= `EXE_RES_ARITHMETIC;
                                    reg1_read_o  <= 1'b1;
                                    reg2_read_o  <= 1'b1;
                                    instvalid    <= `InstValid;
                                end
                                `EXE_MULT: begin  // mult 指令
                                    wreg_o       <= `WriteEnable;
                                    aluop_o      <= `EXE_MULT_OP;
                                    reg1_read_o  <= 1'b1;
                                    reg2_read_o  <= 1'b1;
                                    instvalid    <= `InstValid;
                                end
                                `EXE_MULTU: begin  // multu 指令
                                    wreg_o       <= `WriteEnable;
                                    aluop_o      <= `EXE_MULTU_OP;
                                    reg1_read_o  <= 1'b1;
                                    reg2_read_o  <= 1'b1;
                                    instvalid    <= `InstValid;
                                end
                            default: begin
                            end
                        endcase
                        end
                        default: begin
                    end
                    endcase
                end
                `EXE_SLTI: begin  // slti 指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_SLT_OP;
                    alusel_o    <= `EXE_RES_ARITHMETIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;
                    imm         <= { {16{inst_i[15]}}, inst_i[15:0] };
                    wd_o        <= inst_i[20:16];
                    instvalid   <= `InstValid;
                end
                `EXE_SLTIU: begin  // sltiu 指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_SLTU_OP;
                    alusel_o    <= `EXE_RES_ARITHMETIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;
                    imm         <= { {16{inst_i[15]}}, inst_i[15:0] };
                    wd_o        <= inst_i[20:16];
                    instvalid   <= `InstValid;
                end
                `EXE_ADDI: begin  // addi 指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_ADDI_OP;
                    alusel_o    <= `EXE_RES_ARITHMETIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;
                    imm         <= { {16{inst_i[15]}}, inst_i[15:0] };
                    wd_o        <= inst_i[20:16];
                    instvalid   <= `InstValid;
                end
                `EXE_ADDIU: begin  // addiu 指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_ADDIU_OP;
                    alusel_o    <= `EXE_RES_ARITHMETIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;
                    imm         <= { {16{inst_i[15]}}, inst_i[15:0] };
                    wd_o        <= inst_i[20:16];
                    instvalid   <= `InstValid;
                end
                `EXE_MOVZ: begin  // movz 指令
                    aluop_o     <= `EXE_MOVZ_OP;
                    alusel_o    <= `EXE_RES_MOVE;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b1;
                    instvalid   <= `InstValid;
                    if(reg2_o == `ZeroWord) begin
                        wreg_o <= `WriteEnable;
                    end else begin
                        wreg_o <= `WriteDisable;
                    end
                end
                `EXE_ORI:   begin  // ori 指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_OR_OP;
                    alusel_o    <= `EXE_RES_LOGIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;
                    imm         <= {16'h0, inst_i[15:0]};
                    wd_o        <= inst_i[20:16];
                    instvalid   <= `InstValid;
                end
                `EXE_ANDI:   begin  // andi 指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_AND_OP;
                    alusel_o    <= `EXE_RES_LOGIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;
                    imm         <= {16'h0, inst_i[15:0]};
                    wd_o        <= inst_i[20:16];
                    instvalid   <= `InstValid;
                end
                `EXE_XORI:   begin  // xori 指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_XOR_OP;
                    alusel_o    <= `EXE_RES_LOGIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;
                    imm         <= {16'h0, inst_i[15:0]};
                    wd_o        <= inst_i[20:16];
                    instvalid   <= `InstValid;
                end
                `EXE_LUI:   begin  // lui 指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_OR_OP;
                    alusel_o    <= `EXE_RES_LOGIC;
                    reg1_read_o <= 1'b1;
                    reg2_read_o <= 1'b0;
                    imm         <= {inst_i[15:0], 16'h0};
                    wd_o        <= inst_i[20:16];
                    instvalid   <= `InstValid;
                end
                `EXE_PREF:   begin  // pref 指令
                    wreg_o      <= `WriteDisable;
                    aluop_o     <= `EXE_NOP_OP;
                    alusel_o    <= `EXE_RES_NOP;
                    reg1_read_o <= 1'b0;
                    reg2_read_o <= 1'b0;
                    instvalid   <= `InstValid;
                end
                `EXE_SPECIAL2_INST:  begin
                    case(op3)
                        `EXE_CLZ: begin  // clz 指令
                            wreg_o      <= `WriteEnable;
                            aluop_o     <= `EXE_CLZ_OP;
                            alusel_o    <= `EXE_RES_ARITHMETIC;
                            reg1_read_o <= 1'b1;
                            reg2_read_o <= 1'b0;
                            instvalid   <= `InstValid;
                        end
                        `EXE_CLO: begin  // clo 指令
                            wreg_o      <= `WriteEnable;
                            aluop_o     <= `EXE_CLO_OP;
                            alusel_o    <= `EXE_RES_ARITHMETIC;
                            reg1_read_o <= 1'b1;
                            reg2_read_o <= 1'b0;
                            instvalid   <= `InstValid;
                        end
                        `EXE_MUL: begin  // mul 指令
                            wreg_o      <= `WriteEnable;
                            aluop_o     <= `EXE_MUL_OP;
                            alusel_o    <= `EXE_RES_MUL;
                            reg1_read_o <= 1'b1;
                            reg2_read_o <= 1'b1;
                            instvalid   <= `InstValid;
                        end
                        default: begin
                        end
                    endcase
                end
                `EXE_J: begin
                    wreg_o      <= `WriteDisable;
                    aluop_o     <= `EXE_J_OP;
                    alusel_o    <=  `EXE_RES_JUMP_BRANCH;
                    reg1_read_o <=  1'b0;
                    reg2_read_o <=  1'b0;
                    instvalid   <=  `InstValid;
                    jump_flag_o <= `JumpEnable;
                    jump_target_o <= { pc_i[31:28], inst_i[25:0], 2'b00 }; // 拼接地址
                    flush_o <= `FlushEnable; // 无条件跳转，总是需要冲刷
                    branch_flag_o <= `BranchDisable;
                end
                `EXE_BEQ: begin
                    wreg_o      <= `WriteDisable;
                    aluop_o     <= `EXE_BEQ_OP;
                    alusel_o    <=  `EXE_RES_JUMP_BRANCH;
                    reg1_read_o <=  1'b1;
                    reg2_read_o <=  1'b1;
                    instvalid   <=  `InstValid;
                    branch_flag_o <= (reg1_o == reg2_o); // 判断条件
                    branch_target_o <= pc_i + 4 + { {14{inst_i[15]}}, inst_i[15:0], 2'b00 }; // 计算目标地址
                    if (reg1_o == reg2_o) begin
                        flush_o <= `FlushEnable;
                    end else begin
                        flush_o <= `FlushDisable;
                    end
                    jump_flag_o <= `JumpDisable;
                end
                default:    begin
                end
            endcase
            
            if (inst_i[31:21] == 11'b00000000000) begin
                if (op3 == `EXE_SLL) begin  // sll指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_SLL_OP;
                    alusel_o    <= `EXE_RES_SHIFT;
                    reg1_read_o <= 1'b0;
                    reg2_read_o <= 1'b1;
                    imm[4:0]    <= inst_i[10:6];
                    wd_o        <= inst_i[15:11];
                    instvalid   <= `InstValid;
                end else if (op3 == `EXE_SRL) begin  // srl指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_SRL_OP;
                    alusel_o    <= `EXE_RES_SHIFT;
                    reg1_read_o <= 1'b0;
                    reg2_read_o <= 1'b1;
                    imm[4:0]    <= inst_i[10:6];
                    wd_o        <= inst_i[15:11];
                    instvalid   <= `InstValid;
                end else if (op3 == `EXE_SRA) begin  // sra指令
                    wreg_o      <= `WriteEnable;
                    aluop_o     <= `EXE_SRA_OP;
                    alusel_o    <= `EXE_RES_SHIFT;
                    reg1_read_o <= 1'b0;
                    reg2_read_o <= 1'b1;
                    imm[4:0]    <= inst_i[10:6];
                    wd_o        <= inst_i[15:11];
                    instvalid   <= `InstValid;
                end
            end
            
        end
    end
    
    always @ (*) begin
        if(rst == `RstEnable) begin
            reg1_o <= `ZeroWord;
        end else if((reg1_read_o == 1'b1) && (ex_wreg_i == 1'b1) && (ex_wd_i == reg1_addr_o)) begin
            reg1_o <= ex_wdata_i;
        end else if((reg1_read_o == 1'b1) && (mem_wreg_i == 1'b1) && (mem_wd_i == reg1_addr_o)) begin
            reg1_o <= mem_wdata_i;
        end else if(reg1_read_o == 1'b1) begin
            reg1_o <= reg1_data_i;
        end else if(reg1_read_o == 1'b0) begin
            reg1_o <= imm;
        end else begin    
            reg1_o <= `ZeroWord;
        end  
    end      

    always @ (*) begin
        if(rst == `RstEnable) begin
            reg2_o <= `ZeroWord;
        end else if((reg2_read_o == 1'b1) && (ex_wreg_i == 1'b1) && (ex_wd_i == reg2_addr_o)) begin
            reg2_o <= ex_wdata_i;
        end else if((reg2_read_o == 1'b1) && (mem_wreg_i == 1'b1) && (mem_wd_i == reg2_addr_o)) begin
            reg2_o <= mem_wdata_i;
        end else if(reg2_read_o == 1'b1) begin
            reg2_o <= reg2_data_i;
        end else if(reg2_read_o == 1'b0) begin
            reg2_o <= imm;
        end else begin    
            reg2_o <= `ZeroWord;
        end  
    end    

endmodule