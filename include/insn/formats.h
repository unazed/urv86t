#include "emu.h"
#include "traceback.h"

#define INSN_CASE(funct, enum_) \
  case (funct): canon_insn.insn_ty = enum_; break;
#define INSN_CASE_RET(funct, enum_) \
  case (funct): return enum_;
#define INSN_OP_CASE(opcode, format, grp) \
  case (opcode): canon_insn.insn_ty \
    = rvdec_##format##ty__##grp (state, insn); break;

insn_t rvdec_Rty (rvstate_t state, union insn_base insn);
enum e_insn rvdec_Rty__1 (rvstate_t state, union insn_base insn);
enum e_insn rvdec_Rty__2 (rvstate_t state, union insn_base insn);
#if RV32_HAS(EXT_FD)
insn_t rvdec_R4ty (rvstate_t state, union insn_base insn);
#endif

insn_t rvdec_Ity (rvstate_t state, union insn_base insn);
enum e_insn rvdec_Ity__1 (rvstate_t state, union insn_base insn);
enum e_insn rvdec_Ity__2 (rvstate_t state, union insn_base insn);
enum e_insn rvdec_Ity__3 (rvstate_t state, union insn_base insn);
enum e_insn rvdec_Ity__4 (rvstate_t state, union insn_base insn);
enum e_insn rvdec_Ity__5 (rvstate_t state, union insn_base insn);
#if RV32_HAS(EXT_FD)
enum e_insn rvdec_Ity__6 (rvstate_t state, union insn_base insn);
#endif

insn_t rvdec_Sty (rvstate_t state, union insn_base insn);
enum e_insn rvdec_Sty__1 (rvstate_t state, union insn_base insn);
#if RV32_HAS(EXT_FD)
enum e_insn rvdec_Sty__2 (rvstate_t state, union insn_base insn);
#endif

insn_t rvdec_Uty (rvstate_t state, union insn_base insn);
insn_t rvdec_Jty (rvstate_t state, union insn_base insn);
insn_t rvdec_Bty (rvstate_t state, union insn_base insn);