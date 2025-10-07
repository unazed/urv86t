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
};

typedef struct rvstate* rvstate_t;

__attribute__ (( malloc ))
rvstate_t rvstate_init (u8* const code, size_t len);
void rvstate_free (rvstate_t state);

void* rvmem_at (rvstate_t state, size_t pos);
void* rvmem_at_pc (rvstate_t state, ssize_t offs);
word_t rvmem_reg (rvstate_t state, u8 sel);
word_t* rvmem_regp (rvstate_t state, u8 sel);

bool rvemu_step (rvstate_t state);
void rvemu_dispatch (rvstate_t state, insn_t insn);

insn_t rvdec_insn (rvstate_t state, word_t bytes);