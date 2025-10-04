#include <stdlib.h>

#include "emu.h"
#include "decoder.h"
#include "traceback.h"

rv_state_t
rvstate_alloc (void)
{
  rv_state_t state = calloc (1, sizeof (struct rv_state));
  state->regs = calloc (RISCV_XLEN_BYTES, RISCV_REGCOUNT);
  return state;
}

void
rvstate_free (rv_state_t state)
{
  free (state->regs);
  free (state);
}

bool
rvemu_init (rv_state_t state, u8* const code, size_t len)
{
  (void)len;
  while (state->pc < len)
  {
    insn_t decoded_insn = rvdec_insn (*(word_t *)(code + state->pc));
    (void)decoded_insn;
    state->pc += 4;
  }

  return true;
}