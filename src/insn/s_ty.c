#include "insn/formats.h"

static inline struct insn_ty_argspec_pair
rvdec_Sty__1 (rvstate_t state, union insn_base insn)
{
  switch (insn.s.funct3)
  {
    INSN_CASE_RET(0b000, RV_INSN__SB, RV_ARGSPEC__m8_offs_R32);
    INSN_CASE_RET(0b001, RV_INSN__SH, RV_ARGSPEC__m16_offs_R32);
    INSN_CASE_RET(0b010, RV_INSN__SW, RV_ARGSPEC__m32_offs_R32);
    default:
      rvtrbk_diagn (state, "unrecognised store insn. function bits"); 
      return INVALID_INSN;
  }
}

#if RV32_HAS(EXT_FD)
static inline struct insn_ty_argspec_pair
rvdec_Sty__2 (rvstate_t state, union insn_base insn)
{
  switch (insn.s.funct3)
  {
    case RISCV_FLTFUNC_SINGLE:
    case RISCV_FLTFUNC_DOUBLE:
      return MAKE_INSN(RV_INSN__FSx, RV_ARGSPEC__mX_offs_Fx);
    default:
      rvtrbk_diagn (state, "unrecognised float store insn. function bits"); 
      return INVALID_INSN;
  }
}
#endif

insn_t
rvdec_Sty (rvstate_t state, union insn_base insn)
{
  struct insn_argspec_pair pair = {
    .insn = {
      .rs1 = insn.s.rs1,
      .rs2 = insn.s.rs2,
      .funct = insn.s.funct3,
      .imm = SIGNEXT((insn.s.imm__11_5 << 5) | insn.s.imm__4_0, 1 << 11)
    }
  };

  switch (insn.s.opcode)
  {
    INSN_OP_CASE(RISCV_INSN_S__REG,   S, 1);
#if RV32_HAS(EXT_FD)
    INSN_OP_CASE(RISCV_INSN_S__FLOAT, S, 2);
#endif
  }

  rvasm_emit (state, pair);
  return pair.insn;
}