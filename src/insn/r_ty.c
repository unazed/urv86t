#include "insn/formats.h"

static inline struct insn_ty_argspec_pair
rvdec_Rty__1 (rvstate_t state, union insn_base insn)
{
  (void)state;
  switch ((insn.r.funct7 << 3) | insn.r.funct3)
  {
    INSN_CASE_RET(0b0000000000, RV_INSN__ADD, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0100000000, RV_INSN__SUB, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000000001, RV_INSN__SLL, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000000010, RV_INSN__SLT, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000000011, RV_INSN__SLTU, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000000100, RV_INSN__XOR, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000000101, RV_INSN__SRL, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0100000101, RV_INSN__SRA, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000000110, RV_INSN__OR, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000000111, RV_INSN__AND, RV_ARGSPEC__R32_R32_R32);
#if RV32_HAS(EXT_M)
    INSN_CASE_RET(0b0000001000, RV_INSN__MUL, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000001001, RV_INSN__MULH, RV_ARGSPEC__R32_R32_R32)
    INSN_CASE_RET(0b0000001010, RV_INSN__MULHSU, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000001011, RV_INSN__MULHU, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000001100, RV_INSN__DIV, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000001101, RV_INSN__DIVU, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000001110, RV_INSN__REM, RV_ARGSPEC__R32_R32_R32);
    INSN_CASE_RET(0b0000001111, RV_INSN__REMU, RV_ARGSPEC__R32_R32_R32);
#endif
  }
  return INVALID_INSN;
}

#if RV32_HAS(EXT_FD)
static inline struct insn_ty_argspec_pair
rvdec_Rty__2 (rvstate_t state, union insn_base insn)
{
  (void)state;
  switch (((insn.r.funct7 << 7) | insn.r.rs2) & ~0b000000100000)
  {
    INSN_CASE_RET(0b110000000000, RV_INSN__FCVT_W_x, RV_ARGSPEC__R32_Fx);
    INSN_CASE_RET(0b110000000001, RV_INSN__FCVT_WU_x, RV_ARGSPEC__R32_Fx);
    INSN_CASE_RET(0b110100000000, RV_INSN__FCVT_x_W, RV_ARGSPEC__Fx_R32);
    INSN_CASE_RET(0b110100000001, RV_INSN__FCVT_x_W, RV_ARGSPEC__Fx_R32);
    /* F/D-specific insns.*/
    INSN_CASE_RET(0b111000000000, RV_INSN__FMV_X_W, RV_ARGSPEC__R32_Fx);
    INSN_CASE_RET(0b111100000000, RV_INSN__FMV_W_X, RV_ARGSPEC__Fx_R32);
    INSN_CASE_RET(0b010000000001, RV_INSN__FCVT_S_D, RV_ARGSPEC__Fx_Fx_cvt);
    INSN_CASE_RET(0b010000100000, RV_INSN__FCVT_D_S, RV_ARGSPEC__Fx_Fx_cvt);
    default:
      return INVALID_INSN;
  }
}
#endif

insn_t
rvdec_Rty (rvstate_t state, union insn_base insn)
{
  (void)state;
  struct insn_argspec_pair pair = {
    .insn = {
      .rd = insn.r.rd,
      .rs1 = insn.r.rs1,
      .rs2 = insn.r.rs2,
      .funct = (insn.r.funct7 << 3) | insn.r.funct3
    }
  };

  switch (insn.r.opcode)
  {
    INSN_OP_CASE(RISCV_INSN_R__REG,   R, 1);
#if RV32_HAS(EXT_FD)
    INSN_OP_CASE(RISCV_INSN_R__FLOAT, R, 2);
#endif
  }

  rvasm_emit (state, pair);
  return pair.insn;
}

#if RV32_HAS(EXT_FD)
insn_t
rvdec_R4ty (rvstate_t state, union insn_base insn)
{
  (void)state;
  struct insn_argspec_pair pair = {
    .insn = {
      .rd = insn.r4.rd,
      .rs1 = insn.r4.rs1,
      .rs2 = insn.r4.rs2,
      .rs3 = insn.r4.rs3,
      .funct = insn.r4.funct3
    }
  };

  /* NOTE: I don't understand why they didn't just use the two empty bits
   *       in [25:26] as insn. specifiers opposed to the opcode. 
   */
  switch ((insn.r4.opcode & 0b1100) >> 2)
  {
    INSN_CASE(0b00, RV_INSN__FMADDx, RV_ARGSPEC__Fx_Fx_Fx_Fx);
    INSN_CASE(0b01, RV_INSN__FMSUBx, RV_ARGSPEC__Fx_Fx_Fx_Fx);
    INSN_CASE(0b10, RV_INSN__FNMSUBx, RV_ARGSPEC__Fx_Fx_Fx_Fx);
    INSN_CASE(0b11, RV_INSN__FNMADDx, RV_ARGSPEC__Fx_Fx_Fx_Fx);
  }
  
  return pair.insn;
}
#endif