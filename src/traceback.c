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
      "%s (x%zu): %" PRIx32 "\t%s (x%zu): %" PRIx32
      "\t%s (x%zu): %" PRIx32 "\t%s (x%zu): %" PRIx32 "\n",
      repr_reg_abi_map[i], i, state->regs[i],
      repr_reg_abi_map[i + 1], i + 1, state->regs[i + 1],
      repr_reg_abi_map[i + 2], i + 2, state->regs[i + 2],
      repr_reg_abi_map[i + 3], i + 3, state->regs[i + 3]
    );
  printf ("pc: 0x%" PRIx32 "\n", pc);
  printf ("---/\n");
}

void
rvtrbk_bndcheck_mem (rvstate_t state, word_t addr)
{
  (void)state; (void)addr;
#ifdef RV_SANITIZE
  if (elf_vma_to_mem (state->mem, addr) == NULL)
  {
    rvtrbk_print_dump (state);
    rvtrbk_debug ("tried to access invalid memory: 0x%" PRIx32 "\n", addr);
    rvtrbk_fatal ("invalid memory access");
  }
#endif
}

void
rvtrbk_bndcheck_range (rvstate_t state, word_t start, word_t len)
{
  (void)state; (void)start; (void)len;
#ifdef RV_SANITIZE
  if ((elf_vma_to_mem (state->mem, start) == NULL)
      || elf_vma_to_mem (state->mem, start + len) == NULL)
  {
    rvtrbk_print_dump (state);
    rvtrbk_debug (
      "invalid ranged memory access: [0x%" PRIx32 ", 0x%" PRIx32 "]\n",
      start, start + len);
    rvtrbk_fatal ("invalid memory range access");
  }
#endif
}

void
rvtrbk_bndcheck_jmp (rvstate_t state, iword_t offs)
{
  (void)state; (void)offs;
#ifdef RV_SANITIZE
  if (elf_vma_to_mem (state->mem, state->pc + offs) == NULL)
  {
    rvtrbk_print_dump (state);
    rvtrbk_debug (
      "tried to branch to invalid memory: pc=0x%" PRIx32 "%c0x%" PRIx32 "\n",
      state->pc, (offs < 0)? '-': '+', offs);
    rvtrbk_fatal ("invalid branch address");
  }
#endif
}