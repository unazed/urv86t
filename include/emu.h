#pragma once

#include "platform.h"

#ifdef DEBUG
extern const char* const repr_insn_map[];
extern const char* const repr_reg_abi_map[];
#endif

struct rvstate
{
  struct
  {
    u8* ptr;
    size_t size;
  } mem;
#ifdef EXT_RV32FD
  freg_t fregs[RISCV_FREGCOUNT];
#endif
  reg_t regs[RISCV_REGCOUNT];
  reg_t pc;
  bool suspended;
};

typedef struct rvstate* rvstate_t;

__attribute__ (( malloc ))
rvstate_t rvstate_init (u8* const code, size_t len);
void rvstate_free (rvstate_t state);

void* rvmem_at (rvstate_t state, size_t pos);
void* rvmem_at_pc (rvstate_t state, ssize_t offs);
reg_t rvmem_reg (rvstate_t state, u8 sel);
reg_t* rvmem_regp (rvstate_t state, u8 sel);
#ifdef EXT_RV32FD
freg_t rvmem_freg (rvstate_t state, u8 sel);
freg_t* rvmem_fregp (rvstate_t state, u8 sel);
#endif

bool rvemu_step (rvstate_t state);
void rvemu_dispatch (rvstate_t state, insn_t insn);

insn_t rvdec_insn (rvstate_t state, word_t bytes);