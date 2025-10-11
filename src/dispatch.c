#include "emu.h"
#include "traceback.h"
#include "syscall.h"

#define DISPATCH_BINOP(enum_, op, x, y) \
  case (enum_): state->regs[insn.rd]\
    = (iword_t)rvmem_reg (state, x) op (iword_t)rvmem_reg (state, y); break;
#define DISPATCH_BINOP_I(enum_, op, x) \
  case (enum_): state->regs[insn.rd]\
    = (iword_t)rvmem_reg (state, x) op (iword_t)insn.imm; break;
#define DISPATCH_BINOP_U(enum_, op, x, y) \
  case (enum_): state->regs[insn.rd]\
    = rvmem_reg (state, x) op rvmem_reg (state, y); break;
#define DISPATCH_BINOP_IU(enum_, op, x) \
  case (enum_): state->regs[insn.rd] \
    = rvmem_reg (state, x) op insn.imm; break;

static inline freg_t
rvfloat_nanbox_saturate (u32 val)
{
  return (u64)val | 0xffffffff00000000ull;
}

static inline freg_t
rvfloat_nanbox_unpack (u64 val)
{
  return (u32)(val & 0xffffffff);
}

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
  rvtrbk_debug ("invoked syscall (%" PRIu16 ")\n", syscall_no);
  
  switch (syscall_no)
  {
    case RV_SYSCALL__READ:
      rvtrbk_bndcheck_range (state, *REGARGPn(1), *REGARGPn(2));
      iword_t fd = *REGARGPn(0), count = *REGARGPn(2);
      void* buff = rvmem_at (state, *REGARGPn(1));
      *REGARGPn(0) = rvsysc_read (state, fd, buff, count);
      break;
    default:
      __builtin_unreachable ();
  }
#undef REGARGn
}

void
rvemu_dispatch_debug (rvstate_t state)
{
  (void)state; /* TODO: implement breakpoint? */
  rvtrbk_debug ("invoked debug breakpoint\n");
}

void
rvemu_dispatch (rvstate_t state, insn_t insn)
{
  switch (insn.insn_ty)
  {
    /* Arithmetic/bitwise insns., reg-reg/reg-imm */
    DISPATCH_BINOP(RV_INSN__ADD, +, insn.rs1, insn.rs2);
    DISPATCH_BINOP_I(RV_INSN__ADDI, +, insn.rs1);
    DISPATCH_BINOP(RV_INSN__SUB, -, insn.rs1, insn.rs2);
    DISPATCH_BINOP(RV_INSN__SLL, <<, insn.rs1, insn.rs2);
    DISPATCH_BINOP_I(RV_INSN__SLLI, <<, insn.rs1);
    DISPATCH_BINOP(RV_INSN__SLT, <, insn.rs1, insn.rs2);
    DISPATCH_BINOP_I(RV_INSN__SLTI, <, insn.rs1);
    DISPATCH_BINOP_U(RV_INSN__SLTU, <, insn.rs1, insn.rs2);
    DISPATCH_BINOP_IU(RV_INSN__SLTIU, <, insn.rs1);
    DISPATCH_BINOP_U(RV_INSN__XOR, ^, insn.rs1, insn.rs2);
    DISPATCH_BINOP_IU(RV_INSN__XORI, |, insn.rs1);
    DISPATCH_BINOP_U(RV_INSN__SRL, >>, insn.rs1, insn.rs2);
    DISPATCH_BINOP_IU(RV_INSN__SRLI, >>, insn.rs1);
    DISPATCH_BINOP(RV_INSN__SRA, >>, insn.rs1, insn.rs2);
    DISPATCH_BINOP_I(RV_INSN__SRAI, >>, insn.rs1);
    DISPATCH_BINOP_U(RV_INSN__OR, |, insn.rs1, insn.rs2);
    DISPATCH_BINOP_IU(RV_INSN__ORI, |, insn.rs1);
    DISPATCH_BINOP_U(RV_INSN__AND, &, insn.rs1, insn.rs2);    
    DISPATCH_BINOP_IU(RV_INSN__ANDI, &, insn.rs1);

    /* Load/store insns. */
    case RV_INSN__LB:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *rvmem_regp (state, insn.rd) = (iword_t)(*(i8 *)rvmem_at (
        state, rvmem_reg (state, insn.rs1) + insn.imm));
      break;
    case RV_INSN__LH:
      rvtrbk_bndcheck_mem (state, insn.rs1 + insn.imm);
      *rvmem_regp (state, insn.rd) = (iword_t)(*(i16 *)rvmem_at (
        state, rvmem_reg (state, insn.rs1) + insn.imm));
      break;
    case RV_INSN__LW:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *rvmem_regp (state, insn.rd)
        = *(iword_t *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm);
      break;
    case RV_INSN__LBU:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *rvmem_regp (state, insn.rd)
        = *(u8 *)rvmem_at (state, (u8)rvmem_reg (state, insn.rs1) + insn.imm);
      break;
    case RV_INSN__LHU:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *rvmem_regp (state, insn.rd) = *(hword_t *)rvmem_at (
        state, (hword_t)rvmem_reg (state, insn.rs1) + insn.imm);
      break;
    case RV_INSN__SB:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *(i8 *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm)
        = (i8)rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__SH:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *(hiword_t *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm)
        = (hiword_t)rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__SW:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *(iword_t *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm)
        = (iword_t)rvmem_reg (state, insn.rs2);
      break;

    /* Branch insns. */
    case RV_INSN__BEQ:
      if (rvmem_reg (state, insn.rs1) == rvmem_reg (state, insn.rs2))
      {
        rvtrbk_bndcheck_jmp (state, insn.imm);
        state->pc += (iword_t)insn.imm;
      }
      break;
    case RV_INSN__BNE:
      if (rvmem_reg (state, insn.rs1) != rvmem_reg (state, insn.rs2))
      {
        rvtrbk_bndcheck_jmp (state, insn.imm);
        state->pc += (iword_t)insn.imm;
      }
      break;
    case RV_INSN__BLT:
      if ((iword_t)rvmem_reg (state, insn.rs1)
          < (iword_t)rvmem_reg (state, insn.rs2))
      {
        rvtrbk_bndcheck_jmp (state, insn.imm);
        state->pc += (iword_t)insn.imm;
      }
      break;
    case RV_INSN__BGE:
      if ((iword_t)rvmem_reg (state, insn.rs1)
          >= (iword_t)rvmem_reg (state, insn.rs2))
      {
        rvtrbk_bndcheck_jmp (state, insn.imm);
        state->pc += (iword_t)insn.imm;
      }
      break;
    case RV_INSN__BLTU:
      if (rvmem_reg (state, insn.rs1) < rvmem_reg (state, insn.rs2))
      {
        rvtrbk_bndcheck_jmp (state, insn.imm);
        state->pc += (iword_t)insn.imm;
      }
      break;
    case RV_INSN__BGEU:
      if (rvmem_reg (state, insn.rs1) >= rvmem_reg (state, insn.rs2))
      {
        rvtrbk_bndcheck_jmp (state, insn.imm);
        state->pc += (iword_t)insn.imm;
      }
      break;

    /* Linked branch insns. */
    case RV_INSN__JAL:
      *rvmem_regp (state, insn.rd) = state->pc + RV_INSNLEN;
      state->pc += (iword_t)insn.imm;
      break;
    case RV_INSN__JALR:
      *rvmem_regp (state, insn.rd) = state->pc + RV_INSNLEN;
      state->pc
        = ((iword_t)rvmem_reg (state, insn.rs1) + (iword_t)insn.imm) & ~1;
      break;

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
      break;

    /* CSR insns. */
    case RV_INSN__CSRRW:
    case RV_INSN__CSRRS:
    case RV_INSN__CSRRC:
    case RV_INSN__CSRRWI:
    case RV_INSN__CSRRSI:
    case RV_INSN__CSRRCI:
      rvtrbk_diagn (state, "unimplemented CSR. instructions");
      break;

#ifdef EXT_RV32M
    /* RV32M insns. */
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
      *rvmem_regp (state, insn.rd) = (iword_t)rvmem_reg (state, insn.rs1)
        / (iword_t)rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__DIVU:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) / rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__REM:
      *rvmem_regp (state, insn.rd) = (iword_t)rvmem_reg (state, insn.rs1)
        % (iword_t)rvmem_reg (state, insn.rs2);
      break;
    case RV_INSN__REMU:
      *rvmem_regp (state, insn.rd)
        = rvmem_reg (state, insn.rs1) % rvmem_reg (state, insn.rs2);
      break;
#endif
#ifdef EXT_RV32FD
    case RV_INSN__FLx:
      switch (insn.funct)
      {
        case RISCV_FLTFUNC_SINGLE:
          *rvmem_fregp (state, insn.rd) = rvfloat_nanbox_saturate (
            *rvmem_at_ty (u32, state, rvmem_reg (state, insn.rs1) + insn.imm));
          break;
        case RISCV_FLTFUNC_DOUBLE:
          *rvmem_fregp (state, insn.rd)
            = *rvmem_at_ty (u64, state, rvmem_reg (state, insn.rs1) + insn.imm);
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
    case RV_INSN__FMADDx:
      /* TODO: implement */
    case RV_INSN__FMSUBx:
    case RV_INSN__FNMSUBx:
    case RV_INSN__FNMADDx:
    case RV_INSN__FADDx:
    case RV_INSN__FSUBx:
    case RV_INSN__FMULx:
    case RV_INSN__FDIVx:
    case RV_INSN__FSQRTx:
    case RV_INSN__FSGNJx:
    case RV_INSN__FSGNJNx:
    case RV_INSN__FSGNJXx:
    case RV_INSN__FMINx:
    case RV_INSN__FMAXx:
    case RV_INSN__FEQx:
    case RV_INSN__FLTx:
    case RV_INSN__FLEx:
    case RV_INSN__FCLASSx:

      break;
#endif
    case RV_INSN__INVALID:
      __builtin_unreachable ();
  }
}

#undef DISPATCH_BINOP
#undef DISPATCH_BINOP_I
#undef DISPATCH_BINOP_U
#undef DISPATCH_BINOP_IU