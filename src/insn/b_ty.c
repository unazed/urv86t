#include "insn/formats.h"

insn_t
rvdec_Bty (rvstate_t state, union insn_base insn)
{
  (void)state;
  insn_t canon_insn = {
    .rs1 = insn.b.rs1,
    .rs2 = insn.b.rs2,
    .funct = insn.b.funct3,
    .imm = SIGNEXT(
      (insn.b.imm__12 << 12)
        | (insn.b.imm__11 << 11)
        | (insn.b.imm__10_5 << 5)
        | (insn.b.imm__4_1 << 1),
      1 << 12
    )
  };

  switch (insn.b.funct3)
  {
    INSN_CASE(0b000, RV_INSN__BEQ);
    INSN_CASE(0b001, RV_INSN__BNE);
    INSN_CASE(0b100, RV_INSN__BLT);
    INSN_CASE(0b101, RV_INSN__BGE);
    INSN_CASE(0b110, RV_INSN__BLTU);
    INSN_CASE(0b111, RV_INSN__BGEU);
    default:
      __builtin_unreachable ();
  }

  rvtrbk_debug (
    "\tB-type %s %s, %s, %" PRIi16 "\n",
    repr_insn_map[canon_insn.insn_ty], repr_reg_abi_map[canon_insn.rs1],
    repr_reg_abi_map[canon_insn.rs2], canon_insn.imm
  );

  return canon_insn;
}