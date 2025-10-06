#include <stdlib.h>

#include "traceback.h"

void
rvtrbk_fatal (const char* const msg)
{
  fprintf (stderr, "E: %s", msg);
  exit (EXIT_FAILURE);
}

void
rvtrbk_diagn (rvstate_t state, const char* const msg)
{
  state->suspended = true;
  rvtrbk_error ("%s\n", msg);
}

static inline void
rvtrbrk_pprint_word (word_t n)
{
  printf (
    "%" PRIx8 " %" PRIx8 " %" PRIx8 " %" PRIx8,
    (n & 0xff000000) >> 24,
    (n & 0x00ff0000) >> 16,
    (n & 0x0000ff00) >> 8,
    n & 0x000000ff
  );
}

void
rvtrbk_print_dump (rvstate_t state)
{
  auto pc = state->pc - 4;

  printf ("\\-- CORE DUMP\n");
  for (size_t i = 0; i < RISCV_REGCOUNT; i += 4)
    printf (
      "%s (x%zu): %" PRIu32 "\t%s (x%zu): %" PRIu32
      "\t%s (x%zu): %" PRIu32 "\t%s (x%zu): %" PRIu32 "\n",
      repr_reg_abi_map[i], i, state->regs[i],
      repr_reg_abi_map[i + 1], i + 1, state->regs[i + 1],
      repr_reg_abi_map[i + 2], i + 2, state->regs[i + 2],
      repr_reg_abi_map[i + 3], i + 3, state->regs[i + 3]
    );
  printf ("pc: 0x%" PRIx32 ", prog. size: 0x%zx\n", pc, state->mem.size);
  printf ("--- prev/curr/next insn.\n");
  
  word_t prev_insn
    = (pc >= 4)
    ? *(word_t *)rvmem_at_pc (state, -4)
    : 0;
  auto insn = *(word_t *)rvmem_at_pc (state, 0);
  word_t next_insn
    = (pc <= state->mem.size - 8)
    ? *(word_t *)rvmem_at_pc (state, 4)
    : 0;

  if (prev_insn)
  {
    printf ("<< ");
    rvtrbrk_pprint_word (prev_insn);
    printf (" </ ");
  }
  else
    printf ("<< (n/a) </ ");

  printf ("[ ");
  rvtrbrk_pprint_word (insn);
  printf ("] ");

  if (next_insn)
  {
    printf (">> ");
    rvtrbrk_pprint_word (next_insn);
    printf (" >/");
  }
  else
    printf (">> (n/a) >/");

  printf ("\n---/\n");
}

void
rvtrbk_bndcheck_mem (rvstate_t state, word_t addr)
{
  (void)state; (void)addr;
#ifdef RV_SANITIZE
  if (addr >= state->mem.size)
  {
    rvtrbk_print_dump (state);
    rvtrbk_debug ("tried to access invalid memory: 0x%" PRIx32 "\n", addr);
    rvtrbk_fatal ("invalid memory access");
  }
#endif
}