#include "insn/formats.h"
#include "asm/context.h"

insn_t
rvdec_Jty (rvstate_t state, union insn_base insn)
{
  (void)state;
  struct insn_argspec_pair pair = {
    .insn = {
      .insn_ty = RV_INSN__JAL,
      .rd = insn.j.rd,
      .imm = SIGNEXT(
        (insn.j.imm__20 << 20)
          | (insn.j.imm__19_12 << 12)
          | (insn.j.imm__11 << 11)
          | (insn.j.imm__10_1 << 1),
        1 << 20
      )
    },
    .argspec = RV_ARGSPEC__R32_pcrel
  };

  rvasm_emit (state, pair);
  return pair.insn;
}