#include <stdio.h>
#include <stdlib.h>

#include "emu.h"
#include "traceback.h"

int
main (int argc, char** argv)
{
  if (argc < 2)
  {
    fprintf (stderr, "usage: %s <riscv-binary>\n", argv[0]);
    return EXIT_FAILURE;
  }

  u8* emu_code = NULL;
  rvstate_t emu_state = NULL;

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
    fprintf (stderr,
      "failed to read %zu bytes from file: %s (read %zu)\n", fd_size, argv[1], nread);
    goto clean;
  }

  emu_state = rvstate_init (emu_code, fd_size);
  if (emu_state == NULL)
  {
    fprintf (stderr, "failed to allocate emulation context\n");
    return EXIT_FAILURE;
  } 

  while (rvemu_step (emu_state));
  rvtrbk_print_dump (emu_state);

clean:
  rvstate_free (emu_state);
  free (emu_code);
  fclose (fd);

  return EXIT_SUCCESS;
}