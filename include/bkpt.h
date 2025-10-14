#pragma once

#include "types.h"
#include "platform.h"

#define RV32_FEATURE_BKPT__MAX_BKPT (16)

typedef struct rvstate* rvstate_t;
typedef struct insn_ insn_t;

enum rvbkpt_comparator
{
  BKPTCOMP_NONE = 0, BKPTCOMP_GT, BKPTCOMP_LT, BKPTCOMP_EQ
};

struct rvbkpt_ev__regcond
{
  union
  {
    reg_t val;
    ireg_t sval;
  };
  enum rvbkpt_comparator comp;
  bool sign;
};

struct rvbkpt_ev__insncond
{
  insn_t insn_mask, insn_comp;
};

struct rvbkpt_ev
{
  struct rvbkpt_ev__regcond pc_cond;
  struct rvbkpt_ev__insncond insn_cond;
  bool one_shot, active, triggered;
};

void rvbkpt_add (rvstate_t state, struct rvbkpt_ev* ev);
struct rvbkpt_ev* rvbkpt_poll (rvstate_t state);
void rvbkpt_check_insn (rvstate_t state, insn_t insn);