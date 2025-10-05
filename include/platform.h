#pragma once

#include "types.h"

/* todo: conditional IALIGN based on supported extensions */
#define RISCV_IALIGN_BYTES (4)

#define RISCV_INSN_OPCOND__R(n) ((n) == 0b0110011ul)
#define RISCV_INSN_OPCOND__I(n) \
  ( \
    ((n) == 0b1100111ul) || ((n) == 0b0000011ul) \
    || ((n) == 0b0010011ul) || ((n) == 0b0001111ul) \
    || ((n) == 0b1110011ul) \
  )
#define RISCV_INSN_OPCOND__S(n) ((n) == 0b0100011ul)
#define RISCV_INSN_OPCOND__U(n) \
  (((n) == 0b0010111ul) || ((n) == 0b0110111ul))
#define RISCV_INSN_OPCOND__J(n) ((n) == 0b1101111ul)
#define RISCV_INSN_OPCOND__B(n) ((n) == 0b1100011ul)

#define SIGNEXT(word, sign_bit) \
  (((word) & (sign_bit))? ((word) | ~((sign_bit) - 1)): (word))

#ifdef ENABLE_RV32I
# define RISCV_REGCOUNT (32)
# define RISCV_XLEN_BYTES (4)
typedef u32 reg_t;
#else
# error "Compilation selector for ISA unset"
#endif

typedef u32 word_t;
typedef i32 iword_t;

enum e_insn
{
  RV_INSN__INVALID,
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
  RV_INSN__CSRRCI
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