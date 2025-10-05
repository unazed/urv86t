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
  fprintf (stderr, "e: %s\n", msg);
}

void
rvtrbk_print_dump (rvstate_t state)
{
  (void)state;
}