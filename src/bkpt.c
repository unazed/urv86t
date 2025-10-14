#include <string.h>

#include "bkpt.h"
#include "emu.h"
#include "traceback.h"

#define CHK_COND_MASK(mask, insn, comp, val) \
  (((comp).val & (mask).val) == ((insn).val & (mask).val))  

struct rvbkpt_ev*
rvbkpt_poll (rvstate_t state)
{
  for (size_t ev_idx = 0; ev_idx < RV32_FEATURE_BKPT__MAX_BKPT; ++ev_idx)
  {
    auto ev = &state->bkpt_ev_arr[ev_idx];
    if (!ev->active || !ev->triggered)
      continue;
    if (ev->one_shot)
      ev->active = false;
    return ev;
  }
  return NULL;
}

void
rvbkpt_check_insn (rvstate_t state, insn_t insn)
{
  for (size_t ev_idx = 0; ev_idx < RV32_FEATURE_BKPT__MAX_BKPT; ++ev_idx)
  {
    auto ev = &state->bkpt_ev_arr[ev_idx];

    if (!ev->active)
      continue;
    if (ev->triggered)
    {
      /* If bkpt. is unhandled by next check-iteration, clear it. */
      ev->triggered = false;
      continue;
    }

    insn_t insn_comp = ev->insn_cond.insn_comp,
           insn_mask = ev->insn_cond.insn_mask;
    auto pc = state->pc;
    auto pc_cond = ev->pc_cond;
    bool cond_match = false;

    /* Check instruction match */
    if (insn_comp.insn_ty != RV_INSN__INVALID)
      cond_match = (insn_comp.insn_ty == insn.insn_ty)
        && CHK_COND_MASK(insn_mask, insn, insn_comp, rd)
        && CHK_COND_MASK(insn_mask, insn, insn_comp, rs1)
        && CHK_COND_MASK(insn_mask, insn, insn_comp, rs2)
        && CHK_COND_MASK(insn_mask, insn, insn_comp, funct)
        && CHK_COND_MASK(insn_mask, insn, insn_comp, imm);
    
    /* Check PC match */
    switch (pc_cond.comp)
    {
      case BKPTCOMP_GT:
        cond_match = pc_cond.sign
          ? (iword_t)pc > pc_cond.sval
          : pc > pc_cond.val;
        break;
      case BKPTCOMP_LT:
        cond_match = pc_cond.sign
          ? (iword_t)pc < pc_cond.sval
          : pc < pc_cond.val;
        break;
      case BKPTCOMP_EQ:
        cond_match = pc_cond.sign
          ? (iword_t)pc == pc_cond.sval
          : pc == pc_cond.val;
        break;
      case BKPTCOMP_NONE:
        break;
    }

    ev->triggered = cond_match;
  }
}

void
rvbkpt_add (struct rvstate* state, struct rvbkpt_ev* ev)
{
  for (size_t ev_idx = 0; ev_idx < RV32_FEATURE_BKPT__MAX_BKPT; ++ev_idx)
  {
    auto chk_ev = &state->bkpt_ev_arr[ev_idx];
    if (chk_ev->active)
      continue;
    rvtrbk_debug ("Registering breakpoint in slot #%zu\n", ev_idx);
    memcpy (chk_ev, ev, sizeof (struct rvbkpt_ev));
    return;
  }
  rvtrbk_debug ("No breakpoint slot available\n");
}

#undef CHK_COND_MASK