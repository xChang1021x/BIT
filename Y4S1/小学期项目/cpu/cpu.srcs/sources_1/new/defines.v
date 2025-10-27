`define RstEnable       1'b1
`define RstDisable      1'b0
`define ZeroWord        32'h00000000
`define WriteEnable     1'b1
`define WriteDisable    1'b0
`define ReadEnable      1'b1
`define ReadDisable     1'b0
`define AluOpBus        7:0
`define AluSelBus       2:0
`define InstValid       1'b0
`define InstInvalid     1'b1
`define True_v          1'b1
`define False_v         1'b0
`define ChipEnable      1'b1
`define ChipDisable     1'b0
`define JumpEnable      1'b1
`define JumpDisable     1'b0
`define BranchEnable    1'b1
`define BranchDisable   1'b0
`define FlushEnable     1'b1
`define FlushDisable     1'b0

// 指令码定义
`define EXE_NOP           6'b000000
`define EXE_AND           6'b100100
`define EXE_OR            6'b100101
`define EXE_XOR           6'b100110
`define EXE_NOR           6'b100111
`define EXE_ANDI          6'b001100
`define EXE_ORI           6'b001101
`define EXE_XORI          6'b001110
`define EXE_LUI           6'b001111

`define EXE_SLL           6'b000000
`define EXE_SLLV          6'b000100
`define EXE_SRL           6'b000010
`define EXE_SRLV          6'b000110
`define EXE_SRA           6'b000011
`define EXE_SRAV          6'b000111

`define EXE_SYNC          6'b001111
`define EXE_PREF          6'b110011
`define EXE_SPECIAL_INST  6'b000000
`define EXE_REGIMN_INST   6'b000001
`define EXE_SPECIAL2_INST 6'b011100

`define EXE_MOVZ          6'b001010
`define EXE_MOVN          6'b001011
`define EXE_MFHI          6'b010000
`define EXE_MTHI          6'b010001
`define EXE_MFLO          6'b010010
`define EXE_MTLO          6'b010011

`define EXE_SLT     6'b101010
`define EXE_SLTU    6'b101011
`define EXE_SLTI    6'b001010
`define EXE_SLTIU   6'b001011
`define EXE_ADD     6'b100000
`define EXE_ADDU    6'b100001
`define EXE_SUB     6'b100010
`define EXE_SUBU    6'b100011
`define EXE_ADDI    6'b001000
`define EXE_ADDIU   6'b001001
`define EXE_CLZ     6'b100000
`define EXE_CLO     6'b100001
`define EXE_MULT    6'b011000
`define EXE_MULTU   6'b011001
`define EXE_MUL     6'b000010

`define EXE_J       6'b000010
`define EXE_BEQ     6'b000100
`define EXE_BGTZ    6'b000111
`define EXE_BLEZ    6'b000110
`define EXE_BNE     6'b000101

// AluOp
`define EXE_NOP_OP       8'b00000000
`define EXE_AND_OP       8'b00100100
`define EXE_OR_OP        8'b00100101
`define EXE_XOR_OP       8'b00100110
`define EXE_NOR_OP       8'b00100111

`define EXE_SLL_OP       8'b00000000
`define EXE_SLLV_OP      8'b00000100
`define EXE_SRL_OP       8'b00000010
`define EXE_SRLV_OP      8'b00000110
`define EXE_SRA_OP       8'b00000011
`define EXE_SRAV_OP      8'b00000111

`define EXE_SYNC_OP      8'b00001111
`define EXE_PREF_OP      8'b00001100

`define EXE_MOVZ_OP      8'b00001010
`define EXE_MOVN_OP      8'b00001011
`define EXE_MFHI_OP      8'b00010000
`define EXE_MTHI_OP      8'b00010001
`define EXE_MFLO_OP      8'b00010010
`define EXE_MTLO_OP      8'b00010011

`define EXE_SLT_OP        8'b00101010
`define EXE_SLTU_OP       8'b00101011
`define EXE_ADD_OP        8'b00100000
`define EXE_ADDI_OP       8'b00001000
`define EXE_ADDIU_OP      8'b00001001
`define EXE_ADDU_OP       8'b00100001
`define EXE_SUB_OP        8'b00100010
`define EXE_SUBU_OP       8'b00100011
`define EXE_CLZ_OP        8'b00100000
`define EXE_CLO_OP        8'b00100001
`define EXE_MULT_OP       8'b00000010
`define EXE_MULTU_OP      8'b00011000
`define EXE_MUL_OP        8'b00000010

`define EXE_J_OP          8'b01000000
`define EXE_BEQ_OP        8'b01000001

// AluSel
`define EXE_RES_NOP         3'b000
`define EXE_RES_LOGIC       3'b001
`define EXE_RES_SHIFT       3'b010
`define EXE_RES_MOVE        3'b011
`define EXE_RES_ARITHMETIC  3'b100 
`define EXE_RES_MUL         3'b101 
`define EXE_RES_JUMP_BRANCH 3'b110


//ROM 有关宏定义
`define InstAddrBus     31:0
`define InstBus         31:0
`define InstMemNum      131071
`define InstMemNumLog2  17

//Regfile 有关
`define RegAddrBus      4:0
`define RegBus          31:0
`define RegWidth        32
`define DoubleRegWidth  64
`define DoubleRegBus    63:0
`define RegNum          32
`define RegNumLog2      5
`define NOPRegAddr      5'b00000