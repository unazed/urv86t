#include "insn/formats.h"

insn_t
rvdec_Uty (rvstate_t state, union insn_base insn)
{
  (void)state;
  struct insn_argspec_pair pair = {
    .insn = {
      .rd = insn.u.rd,
      .imm = insn.u.imm__31_12
    }
  };

  switch (insn.u.opcode)
  {
    INSN_CASE(RISCV_INSN_U__LUI, RV_INSN__LUI, RV_ARGSPEC__R32_u20);
    INSN_CASE(RISCV_INSN_U__AUIPC, RV_INSN__AUIPC, RV_ARGSPEC__R32_u20);
  }

  rvasm_emit (state, pair);
  return pair.insn;
}