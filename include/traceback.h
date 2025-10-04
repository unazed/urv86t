#pragma once

#include "emu.h"

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