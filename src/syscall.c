#include <sys/stat.h>
#include <unistd.h>

#include "syscall.h"
#include "traceback.h"
#include "elf.h"

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
  return write (fd, buff, count);
}

RVSYSC_DEFN(rvsysc_exit, iword_t code)
{
  printf ("exited with code (%" PRIi32 ")\n", code);
  state->suspended = true;
  return 0;
}

RVSYSC_DEFN(rvsysc_fstat, iword_t fd, void* buff)
{
  (void)state;
  return fstat (fd, buff);
}

RVSYSC_DEFN(rvsysc_brk, word_t brk)
{
  auto heap = elf_get_heap_region (state->mem);
  u32 min_brk = heap->vma_base,
      current_brk = min_brk + heap->sz_alloc,
      max_brk = heap->vma_base + heap->sz_reserved;
  if ((brk < min_brk) || (brk > max_brk))
    return current_brk;
  heap->sz_alloc += brk - current_brk;
  return brk;
}