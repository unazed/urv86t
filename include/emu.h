#pragma once

#include "platform.h"

#ifdef DEBUG
extern const char* const repr_insn_map[];
extern const char* const repr_reg_abi_map[];
#endif

struct rvstate
{
  /* `regs` determined at run-time, RVxxE/I have different # of regs. */
  bool suspended;
  reg_t* regs;
  reg_t pc;
  struct
  {
    u8* ptr;
    size_t size;
  } mem;
  /* todo: CSRs */
};

typedef struct rvstate* rvstate_t;

__attribute__ (( malloc ))
rvstate_t rvstate_init (u8* const code, size_t len);
void rvstate_free (rvstate_t state);

bool rvemu_step (rvstate_t state);
void rvemu_dispatch (rvstate_t state, insn_t insn);

insn_t rvdec_insn (rvstate_t state, word_t bytes);