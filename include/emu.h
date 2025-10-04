#pragma once

#include "platform.h"

struct rv_state
{
  /* `regs` determined at run-time, RVxxE/I have different # of regs. */
  reg_t* regs;
  reg_t pc;
  struct
  {
    u8* ptr;
    word_t size;
  } mem;
  /* todo: CSRs */
};

typedef struct rv_state* rv_state_t;

__attribute__ (( malloc ))
rv_state_t rv_state_alloc (void);

void rv_state_free (rv_state_t state);

bool rv_emu_init (size_t len;
  rv_state_t state, u8* const code, size_t len);

insn_t rv_insn_decode (word_t bytes);