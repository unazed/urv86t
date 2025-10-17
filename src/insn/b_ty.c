#include "insn/formats.h"

insn_t
rvdec_Bty (rvstate_t state, union insn_base insn)
{
  struct insn_argspec_pair pair = {
    .insn = {
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
    }
  };

  switch (insn.b.funct3)
  {
    INSN_CASE(0b000, RV_INSN__BEQ, RV_ARGSPEC__R32_R32_pcrel);
    INSN_CASE(0b001, RV_INSN__BNE, RV_ARGSPEC__R32_R32_pcrel);
    INSN_CASE(0b100, RV_INSN__BLT, RV_ARGSPEC__R32_R32_pcrel);
    INSN_CASE(0b101, RV_INSN__BGE, RV_ARGSPEC__R32_R32_pcrel);
    INSN_CASE(0b110, RV_INSN__BLTU, RV_ARGSPEC__R32_R32_pcrelu);
    INSN_CASE(0b111, RV_INSN__BGEU, RV_ARGSPEC__R32_R32_pcrelu);
    default:
      rvtrbk_diagn (state, "invalid branch function bit\n");
  }

  rvasm_emit (state, pair);
  return pair.insn;
}