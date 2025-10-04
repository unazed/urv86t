#pragma once

#include <inttypes.h>
#include <stdio.h>

#include "emu.h"

#ifdef DEBUG
# define rv_trbk_debug(fmt, ...) printf (fmt,##__VA_ARGS__)
#else
# define rv_trbk_debug(fmt, ...)
#endif

struct emu_traceback_ctx
{
  struct
  {
    const char* const repr_insn;
    
  } diagnostics;
  const rv_state_t state;
};

extern struct emu_traceback_ctx g_trbk_ctx;

void rv_trbk_init (const char* const src_path);