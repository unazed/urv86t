#pragma once

#include "types.h"

#define RISCV_IALIGN_BYTES (sizeof (word_t))
#define RV_INSNLEN         (sizeof (word_t))

#define RISCV_INSN_I__JALR  (0b1100111)
#define RISCV_INSN_I__LOAD  (0b0000011)
#define RISCV_INSN_I__ARITH (0b0010011)
#define RISCV_INSN_I__SYNCH (0b0001111)
#define RISCV_INSN_I__ENV   (0b1110011)
#define RISCV_INSN_I__FLOAT (0b0000111)
#define RISCV_INSN_OPCOND__I(n) \
  ( \
       ((n) == RISCV_INSN_I__JALR)  || ((n) == RISCV_INSN_I__LOAD) \
    || ((n) == RISCV_INSN_I__ARITH) || ((n) == RISCV_INSN_I__SYNCH) \
    || ((n) == RISCV_INSN_I__ENV)   || ((n) == RISCV_INSN_I__FLOAT) \
  )

#define RISCV_INSN_OPCOND__R(n) ((n) == 0b0110011)

#define RISCV_INSN_S__REG   (0b0100011)
#define RISCV_INSN_S__FLOAT (0b0100111)
#define RISCV_INSN_OPCOND__S(n) \
  (((n) == RISCV_INSN_S__REG) || ((n) == RISCV_INSN_S__FLOAT))

#define RISCV_INSN_U__LUI   (0b0110111)
#define RISCV_INSN_U__AUIPC (0b0010111)
#define RISCV_INSN_OPCOND__U(n) \
  (((n) == RISCV_INSN_U__AUIPC) || ((n) == RISCV_INSN_U__LUI))

#define RISCV_INSN_OPCOND__J(n) ((n) == 0b1101111)
#define RISCV_INSN_OPCOND__B(n) ((n) == 0b1100011)

#define SIGNEXT(word, sign_bit) \
  (((word) & (sign_bit))? ((word) | ~((sign_bit) - 1)): (word))

#ifdef ENABLE_RV32I
# define RISCV_REGCOUNT (32)
# define RISCV_XLEN_BYTES (4)
typedef u32 reg_t;
#else
# error "Compilation selector for ISA unset"
#endif

#ifdef EXT_RV32FD
# define RISCV_FREGCOUNT (32)
# define RISCV_FLEN_BYTES (8)
typedef f64 freg_t;
#endif

typedef u32 word_t;
typedef i32 iword_t;
typedef u16 hword_t;
typedef i16 hiword_t;

enum e_insn
{
  RV_INSN__INVALID,

  /* RV32I insns. */
  RV_INSN__LUI,
  RV_INSN__AUIPC,
  RV_INSN__JAL,
  RV_INSN__JALR,
  RV_INSN__BEQ,
  RV_INSN__BNE,
  RV_INSN__BLT,
  RV_INSN__BGE,
  RV_INSN__BLTU,
  RV_INSN__BGEU,
  RV_INSN__LB,
  RV_INSN__LH,
  RV_INSN__LW,
  RV_INSN__LBU,
  RV_INSN__LHU,
  RV_INSN__SB,
  RV_INSN__SH,
  RV_INSN__SW,
  RV_INSN__ADDI,
  RV_INSN__SLTI,
  RV_INSN__SLTIU,
  RV_INSN__XORI,
  RV_INSN__ORI,
  RV_INSN__ANDI,
  RV_INSN__SLLI,
  RV_INSN__SRLI,
  RV_INSN__SRAI,
  RV_INSN__ADD,
  RV_INSN__SUB,
  RV_INSN__SLL,
  RV_INSN__SLT,
  RV_INSN__SLTU,
  RV_INSN__XOR,
  RV_INSN__SRL,
  RV_INSN__SRA,
  RV_INSN__OR,
  RV_INSN__AND,
  RV_INSN__FENCE,
  RV_INSN__FENCE_I,
  RV_INSN__ECALL,
  RV_INSN__EBREAK,
  RV_INSN__CSRRW,
  RV_INSN__CSRRS,
  RV_INSN__CSRRC,
  RV_INSN__CSRRWI,
  RV_INSN__CSRRSI,
  RV_INSN__CSRRCI,

#ifdef EXT_RV32M
  /* RV32M insns. */
  RV_INSN__MUL,
  RV_INSN__MULH,
  RV_INSN__MULHSU,
  RV_INSN__MULHU,
  RV_INSN__DIV,
  RV_INSN__DIVU,
  RV_INSN__REM,
  RV_INSN__REMU,
#endif

#ifdef EXT_RV32FD
  /* RV32F/D insns. */
  RV_INSN__FLx,
  RV_INSN__FSx,
  RV_INSN__FMADDx,
  RV_INSN__FMSUBx,
  RV_INSN__FNMSUBx,
  RV_INSN__FNMADDx,
  RV_INSN__FADDx,
  RV_INSN__FSUBx,
  RV_INSN__FMULx,
  RV_INSN__FDIVx,
  RV_INSN__FSQRTx,
  RV_INSN__FSGNJx,
  RV_INSN__FSGNJNx,
  RV_INSN__FSGNJXx,
  RV_INSN__FMINx,
  RV_INSN__FMAXx,
  RV_INSN__FCVT_W_x,
  RV_INSN__FCVT_WU_x,
  RV_INSN__FCVT_x_W,
  RV_INSN__FCVT_x_WU,
  RV_INSN__FMV_x_W,
  RV_INSN__FEQx,
  RV_INSN__FLTx,
  RV_INSN__FLEx,
  RV_INSN__FCLASSx,
  RV_INSN__FMV_W_x,
#endif
};

typedef struct
{
  enum e_insn insn_ty;
  u8 rd, rs1, rs2;
  u16 funct;
  word_t imm;
} insn_t;

union insn_base
{
  /* `insn_base.x` is a generic semantic concept, since some instructions
   * don't strictly adhere to their format, and it's clearer to readers than
   * using the R-format to decapsulate another format 
   */
  struct
  {
    word_t opcode : 7;
    word_t rd : 5;
    word_t funct3 : 3;
    word_t rs1 : 5;
    word_t rs2 : 5;
    word_t funct7 : 7;
  } r, x;
  struct
  {
    word_t opcode : 7;
    word_t rd : 5;
    word_t funct3 : 3;
    word_t rs1 : 5;
    word_t imm__11_0 : 12;
  } i;
  struct
  {
    word_t opcode : 7;
    word_t imm__4_0 : 5;
    word_t funct3 : 3;
    word_t rs1 : 5;
    word_t rs2 : 5;
    word_t imm__11_5 : 7;
  } s;
  struct
  {
    word_t opcode : 7;
    word_t imm__11 : 1;
    word_t imm__4_1 : 4;
    word_t funct3 : 3;
    word_t rs1 : 5;
    word_t rs2 : 5;
    word_t imm__10_5 : 6;
    word_t imm__12 : 1;
  } b;
  struct
  {
    word_t opcode : 7;
    word_t rd : 5;
    word_t imm__31_12 : 20;
  } u;
  struct
  {
    word_t opcode : 7;
    word_t rd : 5;
    word_t imm__19_12 : 8;
    word_t imm__11 : 1;
    word_t imm__10_1 : 10;
    word_t imm__20 : 1;
  } j;
  word_t raw; 
};

_Static_assert (sizeof (union insn_base) == sizeof (word_t));