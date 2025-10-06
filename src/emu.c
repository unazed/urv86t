#include <stdlib.h>

#include "emu.h"
#include "traceback.h"

rvstate_t
rvstate_init (u8* const code, size_t len)
{
  rvtrbk_debug ("allocating emulation context\n");
  rvstate_t state = calloc (1, sizeof (struct rvstate));
  if (state == NULL)
    rvtrbk_fatal ("failed to allocate emulation context\n");

  state->regs = calloc (RISCV_XLEN_BYTES, RISCV_REGCOUNT);
  if (state->regs == NULL)
    rvtrbk_fatal ("failed to allocate emulation registers\n");

  state->mem.ptr = code;
  state->mem.size = len;

  return state;
}

void
rvstate_free (rvstate_t state)
{
  rvtrbk_debug ("finalising emulation state\n");
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

void*
rvmem_at (rvstate_t state, size_t pos)
{
  return state->mem.ptr + pos;
}

void*
rvmem_at_pc (rvstate_t state, ssize_t offs)
{
  return rvmem_at (state, state->pc + offs);
}

word_t*
rvmem_regp (rvstate_t state, u8 sel)
{
  return &state->regs[sel];
}

word_t
rvmem_reg (rvstate_t state, u8 sel)
{
  return *rvmem_regp (state, sel);
}

bool
rvemu_step (rvstate_t state)
{
  if (state->suspended)
    return false;
  if (state->pc >= state->mem.size)
    return false;
  auto insn = rvdec_insn (state, rvstate_fetch (state));
  if (insn.insn_ty == RV_INSN__INVALID)
    return false;
  rvemu_dispatch (state, insn);
  return true;
}