#include "insn/formats.h"

enum e_insn
rvdec_Sty__1 (rvstate_t state, union insn_base insn)
{
  switch (insn.s.funct3)
  {
    case 0b000:
      return RV_INSN__SB;
    case 0b001:
      return RV_INSN__SH;
    case 0b010:
      return RV_INSN__SW;
    default:
      rvtrbk_diagn (state, "unrecognised store insn. function bits"); 
      return RV_INSN__INVALID;
  }
}

#if RV32_HAS(EXT_FD)
enum e_insn
rvdec_Sty__2 (rvstate_t state, union insn_base insn)
{
  switch (insn.s.funct3)
  {
    case RISCV_FLTFUNC_SINGLE:
    case RISCV_FLTFUNC_DOUBLE:
      return RV_INSN__FSx;
    default:
      rvtrbk_diagn (state, "unrecognised float store insn. function bits"); 
      return RV_INSN__INVALID;
  }
}
#endif

insn_t
rvdec_Sty (rvstate_t state, union insn_base insn)
{
  insn_t canon_insn = {
    .rs1 = insn.s.rs1,
    .rs2 = insn.s.rs2,
    .funct = insn.s.funct3,
    .imm = SIGNEXT((insn.s.imm__11_5 << 5) | insn.s.imm__4_0, 1 << 11)
  };

  switch (insn.s.opcode)
  {
    INSN_OP_CASE(RISCV_INSN_S__REG,   S, 1);
#if RV32_HAS(EXT_FD)
    INSN_OP_CASE(RISCV_INSN_S__FLOAT, S, 2);
#endif
  }

  rvtrbk_debug (
    "\tS-type %s %s, %s, %" PRIi16 "\n",
    repr_insn_map[canon_insn.insn_ty],
    repr_reg_abi_map[canon_insn.rs1], repr_reg_abi_map[canon_insn.rs2],
    canon_insn.imm
  );
  return canon_insn;
}