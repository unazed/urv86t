#pragma once

#include "types.h"
#include "feature.h"

#define RISCV_IALIGN_BYTES  (sizeof (word_t))
#define RISCV_XLEN_BYTES    (4)
#define RISCV_INSNLEN       (sizeof (word_t))
#define RISCV_REGCOUNT      (32)

#define RISCV_INSN_I__JALR  (0b1100111)
#define RISCV_INSN_I__LOAD  (0b0000011)
#define RISCV_INSN_I__ARITH (0b0010011)
#define RISCV_INSN_I__SYNCH (0b0001111)
#define RISCV_INSN_I__ENV   (0b1110011)

#define RISCV_INSN_OPCOND__I(n) \
  ( \
       ((n) == RISCV_INSN_I__JALR)  || ((n) == RISCV_INSN_I__LOAD) \
    || ((n) == RISCV_INSN_I__ARITH) || ((n) == RISCV_INSN_I__SYNCH) \
    || ((n) == RISCV_INSN_I__ENV)   || ((n) == RISCV_INSN_I__FLOAT) \
  )

#define RISCV_INSN_R__REG   (0b0110011)
#define RISCV_INSN_R__FLOAT (0b1010011)
#define RISCV_INSN_OPCOND__R(n) \
  (((n) == RISCV_INSN_R__REG) || ((n) == RISCV_INSN_R__FLOAT))

#define RISCV_INSN_S__REG   (0b0100011)
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

typedef u32 reg_t;
typedef i32 ireg_t;
typedef u32 word_t;
typedef i32 iword_t;
typedef u16 hword_t;
typedef i16 ihword_t;

#include "feature-nodep.h"

enum e_insn
{
  RV_INSN__INVALID = 0,

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
#if RV32_HAS(EXT_M)
  EXT_RV32M_INSNS,
#endif
#if RV32_HAS(EXT_FD)
  EXT_RV32FD_INSNS,
#endif
#if RV32_HAS(EXT_C)
  EXT_RV32C_INSNS,
#endif
};

typedef struct insn_
{
  enum e_insn insn_ty;
  u8 rd, rs1, rs2;
  u16 funct;
  word_t imm;
} insn_t;

union insn_base
{
  struct
  {
    word_t opcode : 7;
    word_t rd : 5;
    word_t funct3 : 3;
    word_t rs1 : 5;
    word_t rs2 : 5;
    word_t funct7 : 7;
  } r, x;
#if RV32_HAS(EXT_FD)
  struct
  {
    word_t opcode : 7;
    word_t rd : 5;
    word_t funct3 : 3;
    word_t rs1 : 5;
    word_t rs2 : 5;
    word_t funct2 : 2;
    word_t rs3 : 5;
  } r4;
#endif
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
#if RV32_HAS(EXT_C)
  /* `rd_p` (rd'), `rs1_p` (rs1') and `rs2_p` (rs2') refer to
   * `a0`-`a5` (x10-x15), `s0`-`s1` (x8-x9), `sp` (x2) and `ra` (x1)
   */
  struct
  {
    word_t opcode : 2;
    word_t rs2 : 5;
    word_t rd_rs1 : 5;
    word_t funct4 : 4;
  } cr;
  struct
  {
    word_t opcode : 2;
    word_t imm__6_2 : 5;
    word_t rd_rs1 : 5;
    word_t imm__12 : 1;
    word_t funct3 : 3;
  } ci;
  struct
  {
    word_t opcode : 2;
    word_t rs2 : 5;
    word_t imm__12_7 : 6;
    word_t funct3 : 3;
  } css;
  struct
  {
    word_t opcode : 2;
    word_t rd_p : 3;
    word_t imm__12_5 : 8;
    word_t funct3 : 3;
  } ciw;
  struct
  {
    word_t opcode : 2;
    word_t rd_p : 3;
    word_t imm__6_5 : 2;
    word_t rs1_p : 3;
    word_t imm__12_10 : 3;
    word_t funct3 : 3;
  } cl;
  struct
  {
    word_t opcode : 2;
    word_t rs2_p : 3;
    word_t imm__6_5 : 2;
    word_t rs1_p : 3;
    word_t imm__12_10 : 3;
    word_t funct3 : 3;
  } cs;
  struct
  {
    word_t opcode : 2;
    word_t offset__6_2 : 5;
    word_t rs1_p : 3;
    word_t offset__12_10 : 3;
    word_t funct3 : 3;
  } cb;
  struct
  {
    word_t opcode : 2;
    word_t target : 11;
    word_t funct3 : 3;
  } cj;
#endif
  word_t raw; 
};

_Static_assert (sizeof (union insn_base) == sizeof (word_t));

#include "feature-dep.h"