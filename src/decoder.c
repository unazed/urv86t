#include "traceback.h"
#include "insn/formats.h"

insn_t
rvdec_insn (rvstate_t state, word_t bytes)
{
  auto as_base = (union insn_base)bytes;
  if (RISCV_INSN_OPCOND__R(as_base.x.opcode))
  {
    rvtrbk_debug (
      "%" PRIx32 ": decoding R-format insn. (%08" PRIx32 ")\n",
      state->pc, bytes);
    return rvdec_Rty (state, as_base);
  }
  else if (RISCV_INSN_OPCOND__I(as_base.x.opcode))
  {
    rvtrbk_debug (
      "%" PRIx32 ": decoding I-format insn. (%08" PRIx32 ")\n",
      state->pc, bytes);
    return rvdec_Ity (state, as_base);
  }
  else if (RISCV_INSN_OPCOND__S(as_base.x.opcode))
  {
    rvtrbk_debug (
      "%" PRIx32 ": decoding S-format insn. (%08" PRIx32 ")\n",
      state->pc, bytes);
    return rvdec_Sty (state, as_base);
  }
  else if (RISCV_INSN_OPCOND__U(as_base.x.opcode))
  {
    rvtrbk_debug (
      "%" PRIx32 ": decoding U-format insn. (%08" PRIx32 ")\n",
      state->pc, bytes);
    return rvdec_Uty (state, as_base);
  }
  else if (RISCV_INSN_OPCOND__J(as_base.x.opcode))
  {
    rvtrbk_debug (
      "%" PRIx32 ": decoding J-format insn. (%08" PRIx32 ")\n",
      state->pc, bytes);
    return rvdec_Jty (state, as_base);
  }
  else if (RISCV_INSN_OPCOND__B(as_base.x.opcode))
  {
    rvtrbk_debug (
      "%" PRIx32 ": decoding B-format insn. (%08" PRIx32 ")\n",
      state->pc, bytes);
    return rvdec_Bty (state, as_base);
  }
#if RV32_HAS(EXT_FD)
  else if (RISCV_INSN_OPCOND__R4(as_base.x.opcode))
  {
    rvtrbk_debug (
      "%" PRIx32 ": decoding R4-format insn. (%08" PRIx32 ")\n",
      state->pc, bytes);
    return rvdec_R4ty (state, as_base);
  }
#endif
  rvtrbk_error ("failed to parse insn.: %" PRIx32 "\n", bytes);
  rvtrbk_diagn (state, "unrecognised instruction format");
  return (insn_t){ .insn_ty = RV_INSN__INVALID };
}