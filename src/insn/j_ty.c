#include "insn/formats.h"

insn_t
rvdec_Jty (rvstate_t state, union insn_base insn)
{
  (void)state;
  insn_t canon_insn = {
    .insn_ty = RV_INSN__JAL,
    .rd = insn.j.rd,
    .imm = SIGNEXT(
      (insn.j.imm__20 << 20)
        | (insn.j.imm__19_12 << 12)
        | (insn.j.imm__11 << 11)
        | (insn.j.imm__10_1 << 1),
      1 << 20
    )
  };

  rvtrbk_debug (
    "\tJ-type %s %s, %" PRIi16 "\n",
    repr_insn_map[canon_insn.insn_ty], repr_reg_abi_map[canon_insn.rd],
    canon_insn.imm
  );

  return canon_insn;
}