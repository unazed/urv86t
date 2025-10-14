#include <stdio.h>
#include <stdlib.h>

#include "emu.h"
#include "elf.h"
#include "traceback.h"

int
main (int argc, char** argv)
{
  if (argc < 2)
  {
    fprintf (stderr, "usage: %s <riscv-binary>\n", argv[0]);
    return EXIT_FAILURE;
  }

  elfctx_t elf_ctx = NULL;
  u8* emu_code = NULL;
  rvstate_t state = NULL;

  auto fd = fopen (argv[1], "rb");
  if (fd == NULL)
  {
    fprintf (stderr, "failed to open file: '%s'\n", argv[1]);
    return EXIT_FAILURE;
  }

  fseek (fd, 0, SEEK_END);
  size_t fd_size = ftell (fd);
  rewind (fd);

  if ((emu_code = calloc (1, fd_size)) == NULL)
  {
    fprintf (stderr, "failed to allocate memory region for code\n");
    goto clean;
  }

  size_t nread;
  if ((nread = fread (emu_code, 1, fd_size, fd)) != fd_size)
  {
    fprintf (
      stderr, "failed to read %zu bytes from file: %s (read %zu)\n",
      fd_size, argv[1], nread);
    goto clean;
  }

  elf_ctx = elf_init (emu_code, nread);
  if (elf_ctx == NULL)
  {
    fprintf (stderr, "failed to parse executable as ELF file\n");
    goto clean;
  }
  else if (!elf_ctx->bp)
  {
    fprintf (stderr, "failed to allocate stack/heap for emulator\n");
    goto clean;
  }

  state = rvstate_init (elf_ctx);
  if (state == NULL)
  {
    fprintf (stderr, "failed to allocate emulation context\n");
    goto clean;
  }

  rvtrbk_debug (
    "Setting breakpoint at pc: 0x%" PRIx32 "\n", elf_ctx->entry_point);
  struct rvbkpt_ev entry_bkpt = {
    .pc_cond = {
      .val = elf_ctx->entry_point,
      .comp = BKPTCOMP_EQ,
    },
    .one_shot = true, .active = true
  };

  rvbkpt_add (state, &entry_bkpt);

  while (rvemu_step (state))
  {
#if RV32_HAS(BKPT)
    struct rvbkpt_ev* which = NULL;
    if ((which = rvbkpt_poll (state)) == NULL)
      continue;
    rvtrbk_debug ("Triggered breakpoint!\n");
    return 1;
#endif
  }

clean:
  rvstate_free (state);
  elf_free (elf_ctx);
  free (emu_code);
  fclose (fd);

  return EXIT_SUCCESS;
}