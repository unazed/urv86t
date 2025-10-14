#include "syscall.h"
#include "traceback.h"

RVSYSC_DEFN(rvsysc_read, iword_t fd, void* buff, word_t count)
{
  (void)state;
  printf ("read(fd=%" PRIi32 ", buff=%p, count=%" PRIu32 ")\n",
    fd, buff, count);
  return 0;
}

RVSYSC_DEFN(rvsysc_write, iword_t fd, void* buff, word_t count)
{
  (void)state;
  printf ("write(fd=%" PRIi32 ", buff=%p, count=%" PRIu32 ")\n",
    fd, buff, count);
  return 0;
}

RVSYSC_DEFN(rvsysc_exit, iword_t code)
{
  (void)state;
  printf ("exited with code (%" PRIi32 ")\n", code);
  state->suspended = true;
  return 0;
}