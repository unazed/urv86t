#include <math.h>

#include "emu.h"
#include "traceback.h"
#include "syscall.h"

void
rvemu_dispatch_syscall (rvstate_t state)
{
#define REGARGPn(n) (&state->regs[10 + (n)])
  /* Linux syscall ABI
   * https://man7.org/linux/man-pages/man2/syscall.2.html
   * - Syscall no.: `x17` (`a7`)
   * - Args: `x10` (`a0`) -> `x17` (`a7`)
   */

  auto syscall_no = state->regs[17];
  rvtrbk_debug (
    "invoked syscall (%" PRIu16 ", %s) at 0x%" PRIx32 "\n",
    syscall_no, repr_syscall_map[syscall_no], state->pc);
  
  switch (syscall_no)
  {
    case RV_SYSCALL__READ:
    {
      iword_t fd = *REGARGPn(0), count = *REGARGPn(2);
      void* buff = rvmem_at (state, *REGARGPn(1));
      *REGARGPn(0) = rvsysc_read (state, fd, buff, count);
      break;
    }
    case RV_SYSCALL__WRITE:
    {
      iword_t fd = *REGARGPn(0), count = *REGARGPn(2);
      void* buff = rvmem_at (state, *REGARGPn(1));
      *REGARGPn(0) = rvsysc_write (state, fd, buff, count);
      break;
    }
    case RV_SYSCALL__EXIT:
      rvsysc_exit (state, *REGARGPn(0));
      return;
    case RV_SYSCALL__FSTAT:
    {
      void* buff = rvmem_at (state, *REGARGPn(1));
      *REGARGPn(0) = rvsysc_fstat (state, *REGARGPn(0), buff);
      break;
    }
    case RV_SYSCALL__BRK:
      *REGARGPn(0) = rvsysc_brk (state, *REGARGPn(1));
      break;
    default:
      printf ("unrecognized syscall, suspending emulator...\n");
      state->suspended = true;
      return;
  }
#undef REGARGn
}

void
rvemu_dispatch_debug (rvstate_t state)
{
  /* TODO: Perhaps if BKPT ext. is enabled, transfer control. */
  (void)state;
  rvtrbk_debug ("invoked debug breakpoint\n");
}

void
rvemu_dispatch (rvstate_t state, insn_t insn)
{
#if RV32_HAS(BKPT)
  rvbkpt_check_insn (state, insn);
#endif
  i32 pc_offset = RISCV_INSNLEN;
  switch (insn.insn_ty)
  {
    /* Arithmetic/bitwise insns., reg-reg/reg-imm */
    case RV_INSN__ADD:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) + rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__SUB:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) - rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__SLL:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) << (rvmem_reg (state, insn.rs2) & 0x1f);
      break;
    case RV_INSN__SLT:
      *rvmem_regp (state, insn.rd)
        = ((i32)rvmem_reg (state, insn.rs1)
          < (i32)rvmem_reg (state, insn.rs2)) ? 1 : 0;
      break;
    case RV_INSN__SLTU:
      *rvmem_regp (state, insn.rd)
        = (rvmem_reg (state, insn.rs1) < rvmem_reg (state, insn.rs2)) ? 1 : 0;
      break;
    case RV_INSN__XOR:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) ^ rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__SRL:
      *rvmem_regp(state, insn.rd)
        = rvmem_reg (state, insn.rs1) >> (rvmem_reg (state, insn.rs2) & 0x1F);
      break;
    case RV_INSN__SRA:
      *rvmem_regp (state, insn.rd)
        = (u32)((i32)rvmem_reg(state, insn.rs1)
          >> (rvmem_reg(state, insn.rs2) & 0x1F));
      break;
    case RV_INSN__OR:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) | rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__AND:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) & rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__ADDI:
      *rvmem_regp (state, insn.rd) = rvmem_reg (state, insn.rs1) + insn.imm;
      break;
    case RV_INSN__SLLI:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) << (insn.imm & 0x1f);
      break;
    case RV_INSN__SLTI:
      *rvmem_regp (state, insn.rd)
        = ((i32)rvmem_reg (state, insn.rs1) < (i32)insn.imm) ? 1 : 0;
      break;
    case RV_INSN__SLTIU:
      *rvmem_regp (state, insn.rd)
        = (rvmem_reg (state, insn.rs1) < insn.imm) ? 1 : 0;
      break;
    case RV_INSN__XORI:
      *rvmem_regp (state, insn.rd) = rvmem_reg (state, insn.rs1) ^ insn.imm;
      break;
    case RV_INSN__SRLI:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) >> (insn.imm & 0x1F);
      break;
    case RV_INSN__SRAI:
      *rvmem_regp(state, insn.rd)
        = (u32)((i32)rvmem_reg(state, insn.rs1) >> (insn.imm & 0x1F));
      break;
    case RV_INSN__ORI:
      *rvmem_regp (state, insn.rd) = rvmem_reg (state, insn.rs1) | insn.imm;
      break;
    case RV_INSN__ANDI:
      *rvmem_regp (state, insn.rd) = rvmem_reg (state, insn.rs1) & insn.imm;
      break;

    /* Load/store insns. */
    case RV_INSN__LB:
      *rvmem_regp (state, insn.rd)
        = *(i8 *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm);
      break;
    case RV_INSN__LH:
      *rvmem_regp (state, insn.rd)
        = *(i16 *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm);
      break;
    case RV_INSN__LW:
      *rvmem_regp (state, insn.rd)
        = *(i32 *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm);
      break;
    case RV_INSN__LBU:
      *rvmem_regp (state, insn.rd)
        = *(u8 *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm);
      break;
    case RV_INSN__LHU:
      *rvmem_regp (state, insn.rd)
        = *(u16 *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm);
      break;
    case RV_INSN__SB:
      *(i8 *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm)
        = (i8)rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__SH:
      *(i16 *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm)
        = (i16)rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__SW:
      *(i32 *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm)
        = (i32)rvmem_reg (state, insn.rs2);
      break;

    /* Branch insns. */
    case RV_INSN__BEQ:
      if (rvmem_reg (state, insn.rs1) == rvmem_reg (state, insn.rs2))
      {
        state->pc += (iword_t)insn.imm;
        rvtrbk_debug ("-> 0x%" PRIx32 "\n\n", state->pc);
        pc_offset = 0;
      }
      break;
    case RV_INSN__BNE:
      if (rvmem_reg (state, insn.rs1) != rvmem_reg (state, insn.rs2))
      {
        state->pc += (iword_t)insn.imm;
        rvtrbk_debug ("-> 0x%" PRIx32 "\n\n", state->pc);
        pc_offset = 0;
      }
      break;
    case RV_INSN__BLT:
      if ((iword_t)rvmem_reg (state, insn.rs1)
          < (iword_t)rvmem_reg (state, insn.rs2))
      {
        state->pc += (iword_t)insn.imm;
        rvtrbk_debug ("-> 0x%" PRIx32 "\n\n", state->pc);
        pc_offset = 0;
      }
      break;
    case RV_INSN__BGE:
      if ((iword_t)rvmem_reg (state, insn.rs1)
          >= (iword_t)rvmem_reg (state, insn.rs2))
      {
        state->pc += (iword_t)insn.imm;
        rvtrbk_debug ("-> 0x%" PRIx32 "\n\n", state->pc);
        pc_offset = 0;
      }
      break;
    case RV_INSN__BLTU:
      if (rvmem_reg (state, insn.rs1) < rvmem_reg (state, insn.rs2))
      {
        state->pc += (iword_t)insn.imm;
        rvtrbk_debug ("-> 0x%" PRIx32 "\n\n", state->pc);
        pc_offset = 0;
      }
      break;
    case RV_INSN__BGEU:
      if (rvmem_reg (state, insn.rs1) >= rvmem_reg (state, insn.rs2))
      {
        state->pc += (iword_t)insn.imm;
        rvtrbk_debug ("-> 0x%" PRIx32 "\n\n", state->pc);
        pc_offset = 0;
      }
      break;

    /* Linked branch insns. */
    case RV_INSN__JAL:
      *rvmem_regp (state, insn.rd) = state->pc + RISCV_INSNLEN;
      state->pc += (iword_t)insn.imm;
      rvtrbk_debug ("() -> 0x%" PRIx32 "\n\n", state->pc);
      pc_offset = 0;
      break;
    case RV_INSN__JALR:
    {
      word_t target = (rvmem_reg (state, insn.rs1) + insn.imm) & ~1;
      *rvmem_regp (state, insn.rd) = state->pc + RISCV_INSNLEN;
      state->pc = target;
      rvtrbk_debug ("() <-> 0x%" PRIx32 "\n\n", state->pc);
      pc_offset = 0;
      break;
    }

    /* Upper imm. insns. */
    case RV_INSN__LUI:
      *rvmem_regp (state, insn.rd) = insn.imm << 12;
      break;
    case RV_INSN__AUIPC:
      *rvmem_regp (state, insn.rd) = state->pc + (insn.imm << 12);
      break;

    /* Environment insns. */
    case RV_INSN__ECALL:
      rvemu_dispatch_syscall (state);
      break;
    case RV_INSN__EBREAK:
      rvemu_dispatch_debug (state);
      break;

    /* Synch. insns. */
    case RV_INSN__FENCE:
    case RV_INSN__FENCE_I:
      rvtrbk_diagn (state, "unimplemented synch. instructions");
      state->suspended = true;
      break;

    /* CSR insns. */
    case RV_INSN__CSRRW:
    case RV_INSN__CSRRS:
    case RV_INSN__CSRRC:
    case RV_INSN__CSRRWI:
    case RV_INSN__CSRRSI:
    case RV_INSN__CSRRCI:
      rvtrbk_diagn (state, "unimplemented CSR. instructions");
      state->suspended = true;
      break;

#if RV32_HAS(EXT_M)
    case RV_INSN__MUL:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) * rvmem_reg (state, insn.rs2);
      break; 
    case RV_INSN__MULH:
    {
      i64 prod
        = (i64)rvmem_reg (state, insn.rs1) * (i64)rvmem_reg (state, insn.rs2);
      *rvmem_regp (state, insn.rd) = prod >> (RISCV_XLEN_BYTES * 8);
      break;
    }
    case RV_INSN__MULHSU:
    {
      i64 prod
        = (i64)rvmem_reg (state, insn.rs1) * (u64)rvmem_reg (state, insn.rs2);
      *rvmem_regp (state, insn.rd) = prod >> (RISCV_XLEN_BYTES * 8);
      break;
    }
    case RV_INSN__MULHU:
    {
      i64 prod
        = (u64)rvmem_reg (state, insn.rs1) * (u64)rvmem_reg (state, insn.rs2);
      *rvmem_regp (state, insn.rd) = prod >> (RISCV_XLEN_BYTES * 8);
      break;
    }
    case RV_INSN__DIV:
      *rvmem_regp (state, insn.rd)
        = (i32)rvmem_reg (state, insn.rs1) / (i32)rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__DIVU:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) / rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__REM:
      *rvmem_regp (state, insn.rd)
        = (iword_t)rvmem_reg (state, insn.rs1)
          % (iword_t)rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__REMU:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) % rvmem_reg (state, insn.rs2);
      break;
#endif
#if RV32_HAS(EXT_FD)
    case RV_INSN__FLx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          *rvmem_fregp (state, insn.rd) = rvfloat_nanbox_saturate (
            *rvmem_at_ty (u32, state, rvmem_reg (state, insn.rs1) + insn.imm));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          *rvmem_fregp (state, insn.rd) = *rvmem_at_ty (
            u64, state, rvmem_reg (state, insn.rs1) + insn.imm);
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FSx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          *rvmem_at_ty (u32, state, rvmem_reg (state, insn.rs1) + insn.imm) \
            = rvfloat_nanbox_unpack (rvmem_freg (state, insn.rs2));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          *rvmem_at_ty (u64, state, rvmem_reg (state, insn.rs1) + insn.imm) \
            = rvmem_freg (state, insn.rs2);
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FADDx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (state, insn.rd,
            rvfloat_read_f32 (state, insn.rs1) + 
            rvfloat_read_f32 (state, insn.rs2));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (state, insn.rd,
            rvfloat_read_f64 (state, insn.rs1) + 
            rvfloat_read_f64 (state, insn.rs2));
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FSUBx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (state, insn.rd,
            rvfloat_read_f32 (state, insn.rs1) -
            rvfloat_read_f32 (state, insn.rs2));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (state, insn.rd,
            rvfloat_read_f64 (state, insn.rs1) -
            rvfloat_read_f64 (state, insn.rs2));
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FMULx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (state, insn.rd,
            rvfloat_read_f32 (state, insn.rs1) *
            rvfloat_read_f32 (state, insn.rs2));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (state, insn.rd,
            rvfloat_read_f64 (state, insn.rs1) *
            rvfloat_read_f64 (state, insn.rs2));
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FDIVx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (state, insn.rd,
            rvfloat_read_f32 (state, insn.rs1) /
            rvfloat_read_f32 (state, insn.rs2));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (state, insn.rd,
            rvfloat_read_f64 (state, insn.rs1) /
            rvfloat_read_f64 (state, insn.rs2));
          break;
        default:
          __builtin_unreachable ();
      }
      break;

    case RV_INSN__FMADDx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (state, insn.rd,
            rvfloat_read_f32 (state, insn.rs1) *
            rvfloat_read_f32 (state, insn.rs2) +
            rvfloat_read_f32 (state, insn.rs3));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (state, insn.rd,
            rvfloat_read_f64 (state, insn.rs1) *
            rvfloat_read_f64 (state, insn.rs2) +
            rvfloat_read_f64 (state, insn.rs3));
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FMSUBx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (state, insn.rd,
            rvfloat_read_f32 (state, insn.rs1) *
            rvfloat_read_f32 (state, insn.rs2) -
            rvfloat_read_f32 (state, insn.rs3));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (state, insn.rd,
            rvfloat_read_f64 (state, insn.rs1) *
            rvfloat_read_f64 (state, insn.rs2) -
            rvfloat_read_f64 (state, insn.rs3));
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FNMSUBx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (state, insn.rd,
            -rvfloat_read_f32 (state, insn.rs1) *
            rvfloat_read_f32 (state, insn.rs2) +
            rvfloat_read_f32 (state, insn.rs3));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (state, insn.rd,
            -rvfloat_read_f64 (state, insn.rs1) *
            rvfloat_read_f64 (state, insn.rs2) +
            rvfloat_read_f64 (state, insn.rs3));
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FNMADDx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (state, insn.rd,
            -rvfloat_read_f32 (state, insn.rs1) *
            rvfloat_read_f32 (state, insn.rs2) -
            rvfloat_read_f32 (state, insn.rs3));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (state, insn.rd,
            -rvfloat_read_f64 (state, insn.rs1) *
            rvfloat_read_f64 (state, insn.rs2) -
            rvfloat_read_f64 (state, insn.rs3));
          break;
        default:
          __builtin_unreachable ();
      }
      break;

    case RV_INSN__FSQRTx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (
            state, insn.rd, sqrtf (rvfloat_read_f32 (state, insn.rs1)));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (
            state, insn.rd, sqrt (rvfloat_read_f64 (state, insn.rs1)));
          break;
        default:
          __builtin_unreachable ();
      }
      break;

    case RV_INSN__FSGNJx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (
            state, insn.rd,
            copysignf (
              rvfloat_read_f32 (state, insn.rs1),
              rvfloat_read_f32 (state, insn.rs2)));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (
            state, insn.rd,
            copysign (
              rvfloat_read_f64 (state, insn.rs1),
              rvfloat_read_f64 (state, insn.rs2)));
          break;
        default:
          __builtin_unreachable ();
      }
      break;

    case RV_INSN__FSGNJNx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_write_f32 (
            state, insn.rd,
            copysignf (
              rvfloat_read_f32 (state, insn.rs1),
              -rvfloat_read_f32 (state, insn.rs2)));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_write_f64 (
            state, insn.rd,
            copysign (
              rvfloat_read_f64 (state, insn.rs1),
              -rvfloat_read_f64 (state, insn.rs2)));
          break;
        default:
          __builtin_unreachable ();
      }
      break;

    case RV_INSN__FSGNJXx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          {
            f32 a = rvfloat_read_f32 (state, insn.rs1);
            f32 b = rvfloat_read_f32 (state, insn.rs2);
            u32 sign_xor
              = (rvfloat_as_u32 (a) ^ rvfloat_as_u32 (b)) & 0x80000000;
            rvfloat_write_f32 (
              state, insn.rd,
              rvfloat_as_f32 ((rvfloat_as_u32 (a) & 0x7FFFFFFF) | sign_xor));
          }
          break;
        case RISCV_FLTFUNC_DOUBLE:
        {
          f64 a = rvfloat_read_f64 (state, insn.rs1);
          f64 b = rvfloat_read_f64 (state, insn.rs2);
          u64 sign_xor
            = (rvfloat_as_u64 (a) ^ rvfloat_as_u64 (b)) & 0x8000000000000000ULL;
          rvfloat_write_f64 (
            state, insn.rd,
            rvfloat_as_f64 (
              (rvfloat_as_u64 (a) & 0x7FFFFFFFFFFFFFFFULL) | sign_xor));
          break;
        }
        default:
          __builtin_unreachable ();
      }
      break;

    case RV_INSN__FMINx:
    case RV_INSN__FMAXx:

    case RV_INSN__FEQx:
    case RV_INSN__FLTx:
    case RV_INSN__FLEx:

    case RV_INSN__FCLASSx:
      rvtrbk_debug ("unimplemented fp insn.!\n");
      state->suspended = true;
      return;

    case RV_INSN__FCVT_x_W:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_cvt_f32_from_i32 (
            state, insn.rd, (i32)rvmem_reg (state, insn.rs1));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_cvt_f64_from_i32 (
            state, insn.rd, (i32)rvmem_reg (state, insn.rs1));
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FCVT_x_WU:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          rvfloat_cvt_f32_from_i32 (
            state, insn.rd, rvmem_reg (state, insn.rs1));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          rvfloat_cvt_f64_from_i32 (
            state, insn.rd, rvmem_reg (state, insn.rs1));
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FCVT_W_x:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          *rvmem_regp (state, insn.rd)
            = (i32)rvfloat_read_f32 (state, insn.rs1);
          break;
        case RISCV_FLTFUNC_DOUBLE:
          *rvmem_regp (state, insn.rd)
            = (i32)rvfloat_read_f64 (state, insn.rs1);
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FCVT_WU_x:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          *rvmem_regp (state, insn.rd)
            = (u32)rvfloat_read_f32 (state, insn.rs1);
          break;
        case RISCV_FLTFUNC_DOUBLE:
          *rvmem_regp (state, insn.rd)
            = (u32)rvfloat_read_f64 (state, insn.rs1);
          break;
        default:
          __builtin_unreachable ();
      }
      break;
    case RV_INSN__FMV_X_W:
      *rvmem_regp (state, insn.rd)
        = rvfloat_nanbox_unpack (rvmem_freg (state, insn.rs1));
      break;
    case RV_INSN__FMV_W_X:
      *rvmem_fregp (state, insn.rd)
        = rvfloat_nanbox_saturate (rvmem_reg (state, insn.rs1));
      break;
    case RV_INSN__FCVT_S_D:
      rvfloat_write_f32 (state, insn.rd, 
        (f32)rvfloat_read_f64 (state, insn.rs1));
      break;
    case RV_INSN__FCVT_D_S:
      rvfloat_write_f64 (state, insn.rd, 
        (f64)rvfloat_read_f32 (state, insn.rs1));
      break;
#endif
#if RV32_HAS(EXT_C)
    case RV_INSN__C_NOP:
    case RV_INSN__C_ADDI:
    case RV_INSN__C_JAL:
    case RV_INSN__C_LI:
    case RV_INSN__C_ADDI16SP:
    case RV_INSN__C_LUI:
    case RV_INSN__C_SRLI:
    case RV_INSN__C_SRAI:
    case RV_INSN__C_ANDI:
    case RV_INSN__C_SUB:
    case RV_INSN__C_XOR:
    case RV_INSN__C_OR:
    case RV_INSN__C_AND:
    case RV_INSN__C_J:
    case RV_INSN__C_BEQZ:
    case RV_INSN__C_BNEZ:
    case RV_INSN__C_ADDI4SPN:
    case RV_INSN__C_FLD:
    case RV_INSN__C_LW:
    case RV_INSN__C_FLW:
    case RV_INSN__C_FSD:
    case RV_INSN__C_SW:
    case RV_INSN__C_FSW:
    case RV_INSN__C_SLLI:
    case RV_INSN__C_SLLI64:
    case RV_INSN__C_FLDSP:
    case RV_INSN__C_LWSP:
    case RV_INSN__C_FLWSP:
    case RV_INSN__C_JR:
    case RV_INSN__C_MV:
    case RV_INSN__C_EBREAK:
    case RV_INSN__C_JALR:
    case RV_INSN__C_ADD:
    case RV_INSN__C_FSDSP:
    case RV_INSN__C_SWSP:
    case RV_INSN__C_FSWSP:
      rvtrbk_diagn (state, "Compressed insns. not implemented\n");
      state->suspended = true;
      break;
#endif
    case RV_INSN__INVALID:
      __builtin_unreachable ();
  }

  state->pc += pc_offset;
}