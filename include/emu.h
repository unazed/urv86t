#pragma once

#include "platform.h"

#ifdef DEBUG
extern const char* const repr_insn_map[];
extern const char* const repr_reg_abi_map[];
#endif

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
rv_state_t rvstate_alloc (void);

void rvstate_free (rv_state_t state);

bool rvemu_init (size_t len;
  rv_state_t state, u8* const code, size_t len);