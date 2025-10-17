#include <stdlib.h>

#include "emu.h"
#include "traceback.h"
#include "elf.h"

rvstate_t
rvstate_init (elfctx_t ctx)
{
  rvtrbk_debug ("Allocating emulation context\n");
  rvstate_t state = calloc (1, sizeof (struct rvstate));
  if (state == NULL)
    rvtrbk_fatal ("failed to allocate emulation context\n");
  state->mem = ctx;
  state->pc = ctx->entry_point;
  state->regs[2] = ctx->sp;
  return state;
}

void
rvstate_free (rvstate_t state)
{
  rvtrbk_debug ("Finalising emulation state\n");
  free (state);
}

static word_t
rvstate_fetch (rvstate_t state)
{
  auto insn_ptr = elf_vma_to_mem (state->mem, state->pc);
  if (insn_ptr == NULL)
  {
    rvtrbk_debug ("Failed to fetch from pc: 0x%" PRIx32 "\n", state->pc);
    return 0;
  }
  return *(word_t *)insn_ptr;
}

void*
rvmem_at (rvstate_t state, u32 addr)
{
  void* ptr = (void *)elf_vma_to_mem (state->mem, addr);
  if (ptr == NULL)
  {
    rvtrbk_debug ("tried to fetch out of bounds insn.: 0x%" PRIx32 "\n", addr);
    state->suspended = true;
    return NULL;
  }
  return ptr;
}

void*
rvmem_at_pc (rvstate_t state, i32 offs)
{
  return rvmem_at (state, state->pc + offs);
}

reg_t*
rvmem_regp (rvstate_t state, u8 sel)
{
  return &state->regs[sel];
}

reg_t
rvmem_reg (rvstate_t state, u8 sel)
{
  return *rvmem_regp (state, sel);
}

#if RV32_HAS(EXT_FD)
freg_t*
rvmem_fregp (rvstate_t state, u8 sel)
{
  return &state->fregs[sel];
}

freg_t
rvmem_freg (rvstate_t state, u8 sel)
{
  return *rvmem_fregp (state, sel);
}
#endif

bool
rvemu_step (rvstate_t state)
{
  if (state->suspended)
    return false;
  state->regs[0] = 0;
  auto insn = rvdec_insn (state, rvstate_fetch (state));
  if (insn.insn_ty == RV_INSN__INVALID)
  {
    rvtrbk_error ("tried to decode invalid instruction\n");
    return false;
  }
  rvemu_dispatch (state, insn);
  return true;
}