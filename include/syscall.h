#pragma once

#include "emu.h"

#define RVSYSC_DEFN(name, ...) \
  iword_t name (rvstate_t state,##__VA_ARGS__)

#define RV_SYSCALL__READ  (63)
#define RV_SYSCALL__WRITE (64)
#define RV_SYSCALL__EXIT  (93)

RVSYSC_DEFN(rvsysc_read, iword_t fd, void* buff, word_t count);
RVSYSC_DEFN(rvsysc_write, iword_t fd, void* buff, word_t count);
RVSYSC_DEFN(rvsysc_exit, iword_t code);