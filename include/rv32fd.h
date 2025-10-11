#pragma once

#include "types.h"

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
  RV_INSN__FLEx

#define RISCV_FREGCOUNT (32)
#define RISCV_FLEN_BYTES (8)

#define RISCV_INSN_OPCOND__R4(n) ((n) == 0b1000011)
#define RISCV_INSN_I__FLOAT (0b0000111)
#define RISCV_INSN_S__FLOAT (0b0100111)
#define RISCV_FLTFUNC_SINGLE (0b010)
#define RISCV_FLTFUNC_DOUBLE (0b011)

typedef u64 freg_t;