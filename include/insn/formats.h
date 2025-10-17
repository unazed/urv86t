#include "emu.h"
#include "traceback.h"
#include "asm/context.h"

#define INSN_CASE(funct, enum_, argspec_) \
  case (funct): \
    pair.insn.insn_ty = (enum_); \
    pair.argspec = (argspec_); \
    break;
#define INSN_CASE_RET(funct, enum_, argspec_) \
  case (funct): return MAKE_INSN(enum_, argspec_);
#define INSN_OP_CASE(opcode, format, grp) \
  case (opcode): \
  { \
    auto insn_ty_argspec = rvdec_##format##ty__##grp (state, insn); \
    pair.argspec = insn_ty_argspec.argspec; \
    pair.insn.insn_ty = insn_ty_argspec.insn_ty; \
    break; \
  }
#define MAKE_INSN(enum_, argspec_) \
  (struct insn_ty_argspec_pair){ .insn_ty = (enum_), .argspec = (argspec_)}
#define INVALID_INSN \
  (struct insn_ty_argspec_pair){ \
    .insn_ty = RV_INSN__INVALID, .argspec = RV_ARGSPEC__NONE }

struct insn_argspec_pair
{
  enum e_insn_argspec argspec;
  insn_t insn;
};

struct insn_ty_argspec_pair
{
  enum e_insn_argspec argspec;
  enum e_insn insn_ty;
};

#if RV32_HAS(EXT_FD)
insn_t rvdec_R4ty (rvstate_t state, union insn_base insn);
#endif

insn_t rvdec_Rty (rvstate_t state, union insn_base insn);
insn_t rvdec_Ity (rvstate_t state, union insn_base insn);
insn_t rvdec_Sty (rvstate_t state, union insn_base insn);
insn_t rvdec_Uty (rvstate_t state, union insn_base insn);
insn_t rvdec_Jty (rvstate_t state, union insn_base insn);
insn_t rvdec_Bty (rvstate_t state, union insn_base insn);