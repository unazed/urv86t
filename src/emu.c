#include <stdlib.h>

#include "emu.h"
#include "traceback.h"

rvstate_t
rvstate_init (u8* const code, size_t len)
{
  rvstate_t state = calloc (1, sizeof (struct rvstate));
  state->regs = calloc (RISCV_XLEN_BYTES, RISCV_REGCOUNT);
  state->mem.ptr = code;
  state->mem.size = len;
  return state;
}

void
rvstate_free (rvstate_t state)
{
  free (state->regs);
  free (state);
}

static word_t
rvstate_fetch (rvstate_t state)
{
  auto insn = *(word_t *)(state->mem.ptr + state->pc);
  state->pc += sizeof (word_t);
  return insn;
}

bool
rvemu_init (rvstate_t state)
{
  while (state->pc < state->mem.size)
  {
    auto insn = rvdec_insn (rvstate_fetch (state));
    if (insn.insn_ty == RV_INSN__INVALID)
      return false;
    rvemu_dispatch (state, insn);
  }
  return true;
}