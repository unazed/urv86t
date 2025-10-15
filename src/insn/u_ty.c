#include "insn/formats.h"

insn_t
rvdec_Uty (rvstate_t state, union insn_base insn)
{
  (void)state;
  insn_t canon_insn = {
    .rd = insn.u.rd,
    .imm = insn.u.imm__31_12
  };

  switch (insn.u.opcode)
  {
    INSN_CASE(RISCV_INSN_U__LUI, RV_INSN__LUI);
    INSN_CASE(RISCV_INSN_U__AUIPC, RV_INSN__AUIPC);
  }

  rvtrbk_debug (
    "\tU-type %s %s, %" PRIu32 "\n",
    repr_insn_map[canon_insn.insn_ty],
    repr_reg_abi_map[canon_insn.rd], canon_insn.imm
  );

  return canon_insn;
}