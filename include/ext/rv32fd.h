#pragma once

#include "types.h"

typedef struct rvstate* rvstate_t;

#define EXT_RV32FD_INSNS \
  RV_INSN__FLx, \
  RV_INSN__FSx, \
  RV_INSN__FMADDx, \
  RV_INSN__FMSUBx, \
  RV_INSN__FNMSUBx, \
  RV_INSN__FNMADDx, \
  RV_INSN__FADDx, \
  RV_INSN__FSUBx, \
  RV_INSN__FMULx, \
  RV_INSN__FDIVx, \
  RV_INSN__FSQRTx, \
  RV_INSN__FSGNJx, \
  RV_INSN__FSGNJNx, \
  RV_INSN__FSGNJXx, \
  RV_INSN__FMINx, \
  RV_INSN__FMAXx, \
  RV_INSN__FEQx, \
  RV_INSN__FLTx, \
  RV_INSN__FCLASSx, \
  RV_INSN__FLEx, \
  RV_INSN__FCVT_x_W, \
  RV_INSN__FCVT_x_WU, \
  RV_INSN__FCVT_W_x, \
  RV_INSN__FCVT_WU_x, \
  RV_INSN__FMV_X_W, \
  RV_INSN__FMV_W_X, \
  RV_INSN__FCVT_S_D, \
  RV_INSN__FCVT_D_S

#define RISCV_FREGCOUNT   (32)
#define RISCV_FLEN_BYTES  (8)

#define RISCV_INSN_OPCOND__R4(n) \
  (  ((n) == 0b1000011) || ((n) == 0b1000111) \
  || ((n) == 0b1001011) || ((n) == 0b1001111))
#define RISCV_INSN_R__FLOAT       (0b1010011)
#define RISCV_INSN_I__FLOAT       (0b0000111)
#define RISCV_INSN_S__FLOAT       (0b0100111)
#define RISCV_FLTFUNC_SINGLE      (0b010)
#define RISCV_FLTFUNC_DOUBLE      (0b011)

typedef u64 freg_t;

freg_t rvfloat_nanbox_saturate (u32 val);
freg_t rvfloat_nanbox_unpack (u64 val);
f32 rvfloat_read_f32 (rvstate_t state, u8 freg);
f64 rvfloat_read_f64 (rvstate_t state, u8 freg);
f64 rvfloat_as_f64 (u64 val);
u64 rvfloat_as_u64(f64 val);
f32 rvfloat_as_f32 (u32 val);
u32 rvfloat_as_u32 (f32 val);
void rvfloat_write_f32 (rvstate_t state, u8 freg, f32 val);
void rvfloat_write_f64 (rvstate_t state, u8 freg, f64 val);
void rvfloat_cvt_f32_from_i32 (rvstate_t state, u8 freg, i32 val);
void rvfloat_cvt_f32_from_u32 (rvstate_t state, u8 freg, u32 val);
void rvfloat_cvt_f64_from_i32 (rvstate_t state, u8 freg, i32 val);
void rvfloat_cvt_f64_from_u32 (rvstate_t state, u8 freg, u32 val);