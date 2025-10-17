#pragma once

#include <stdio.h>

typedef struct rvstate *rvstate_t;
struct insn_argspec_pair;

typedef struct rvasm_ctx
{
  const char* out_path;
  FILE* out_fd;
} *rvasm_ctx_t;

enum e_insn_argspec
{
  RV_ARGSPEC__NONE,
  RV_ARGSPEC__R32_R32_R32,
  RV_ARGSPEC__R32_R32_i12,
  RV_ARGSPEC__R32_R32_u12,
  RV_ARGSPEC__R32_R32_u5,
  RV_ARGSPEC__R32_m8_offs,
  RV_ARGSPEC__R32_m8u_offs,
  RV_ARGSPEC__R32_m16_offs,
  RV_ARGSPEC__R32_m16u_offs,
  RV_ARGSPEC__R32_m32_offs,
  RV_ARGSPEC__m8_offs_R32,
  RV_ARGSPEC__m16_offs_R32,
  RV_ARGSPEC__m32_offs_R32,
  RV_ARGSPEC__R32_R32_pcrel,
  RV_ARGSPEC__R32_R32_pcrelu,
  RV_ARGSPEC__R32_pcrel,
  RV_ARGSPEC__R32_u20,
  RV_ARGSPEC__R32_csr_R32,
  RV_ARGSPEC__R32_csr_u5,
#if RV32_HAS(EXT_FD)
  RV_ARGSPEC__Fx_Fx_Fx,
  RV_ARGSPEC__Fx_Fx_Fx_Fx,
  RV_ARGSPEC__Fx_Fx,
  RV_ARGSPEC__Fx_mX_offs,
  RV_ARGSPEC__mX_offs_Fx,
  RV_ARGSPEC__R32_Fx_Fx,
  RV_ARGSPEC__R32_Fx,
  RV_ARGSPEC__Fx_R32,
  RV_ARGSPEC__Fx_Fx_cvt,
#endif
};

__attribute__ (( malloc ))
rvasm_ctx_t rvasm_init (const char* const path);
void rvasm_free (rvasm_ctx_t ctx);
void rvasm_emit (rvstate_t state, struct insn_argspec_pair pair);