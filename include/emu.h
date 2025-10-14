#pragma once

#include "platform.h"

#define rvmem_at_ty(ty, state, pos) (ty *)rvmem_at ((state), (pos))

typedef struct elf_context* elfctx_t;

typedef struct rvstate
{
#if RV32_HAS(EXT_FD)
  freg_t fregs[RISCV_FREGCOUNT];
#endif
  reg_t regs[RISCV_REGCOUNT];
#if RV32_HAS(BKPT)
  struct rvbkpt_ev bkpt_ev_arr[RV32_FEATURE_BKPT__MAX_BKPT];
#endif
  elfctx_t mem;
  reg_t pc;
  bool suspended;
} *rvstate_t;

__attribute__ (( malloc ))
rvstate_t rvstate_init (elfctx_t ctx);
void rvstate_free (rvstate_t state);

void* rvmem_at (rvstate_t state, u32 addr);
void* rvmem_at_pc (rvstate_t state, i32 offs);
reg_t rvmem_reg (rvstate_t state, u8 sel);
reg_t* rvmem_regp (rvstate_t state, u8 sel);

#if RV32_HAS(EXT_FD)
freg_t rvmem_freg (rvstate_t state, u8 sel);
freg_t* rvmem_fregp (rvstate_t state, u8 sel);
#endif

bool rvemu_step (rvstate_t state);
void rvemu_dispatch (rvstate_t state, insn_t insn);
#if RV32_HAS(BKPT)
struct rvbkpt_ev* rvemu_bkpt_poll (rvstate_t state);
#endif

insn_t rvdec_insn (rvstate_t state, word_t bytes);

extern const char* const repr_insn_map[];
extern const char* const repr_reg_abi_map[];