#pragma once

#define EXT_RV32C_INSNS \
  RV_INSN__C_NOP, \
  RV_INSN__C_ADDI, \
  RV_INSN__C_JAL, \
  RV_INSN__C_LI, \
  RV_INSN__C_ADDI16SP, \
  RV_INSN__C_LUI, \
  RV_INSN__C_SRLI, \
  RV_INSN__C_SRAI, \
  RV_INSN__C_ANDI, \
  RV_INSN__C_SUB, \
  RV_INSN__C_XOR, \
  RV_INSN__C_OR, \
  RV_INSN__C_AND, \
  RV_INSN__C_J, \
  RV_INSN__C_BEQZ, \
  RV_INSN__C_BNEZ, \
  RV_INSN__C_ADDI4SPN, \
  RV_INSN__C_FLD, \
  RV_INSN__C_LW, \
  RV_INSN__C_FLW, \
  RV_INSN__C_FSD, \
  RV_INSN__C_SW, \
  RV_INSN__C_FSW, \
  RV_INSN__C_SLLI, \
  RV_INSN__C_SLLI64, \
  RV_INSN__C_FLDSP, \
  RV_INSN__C_LWSP, \
  RV_INSN__C_FLWSP, \
  RV_INSN__C_JR, \
  RV_INSN__C_MV, \
  RV_INSN__C_EBREAK, \
  RV_INSN__C_JALR, \
  RV_INSN__C_ADD, \
  RV_INSN__C_FSDSP, \
  RV_INSN__C_SWSP, \
  RV_INSN__C_FSWSP

/* Compressed insns. have 3 groupings, with no particular opcode mapping
 * to the instruction formats
 */