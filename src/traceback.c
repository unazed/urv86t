#include <stdlib.h>

#include "traceback.h"
#include "elf.h"

void
rvtrbk_fatal (const char* const msg)
{
  fprintf (stderr, "E: %s", msg);
  __builtin_trap ();
  exit (EXIT_FAILURE);
}

void
rvtrbk_diagn (rvstate_t state, const char* const msg)
{
  state->suspended = true;
  rvtrbk_error ("%s\n", msg);
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

  printf ("--- %zu memory region(s)\n", state->mem->nr_regions);

  for (size_t i = 0; i < state->mem->nr_regions; ++i)
  {
    auto region = &state->mem->load_regions[i];
    printf (
      "#%zu: 0x%08" PRIx32 "\t-> 0x%08" PRIx32 " (%s)\n",
      i, region->vma_base, region->vma_base + region->sz_reserved,
      region->tag? region->tag: "untagged");
  }
}