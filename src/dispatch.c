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
  case (enum_): state->regs[insn.rd]\
    = rvmem_reg (state, x) op insn.imm; break;

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
        = (i8)insn.imm;
      break;
    case RV_INSN__SH:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *(hiword_t *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm)
        = (hiword_t)insn.imm;
      break;
    case RV_INSN__SW:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *(iword_t *)rvmem_at (state, rvmem_reg (state, insn.rs1) + insn.imm)
        = (iword_t)insn.imm;
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
      state->pc = (iword_t)rvmem_reg (state, insn.rs1) + (iword_t)insn.imm;
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

    /* CSR insns. */
    case RV_INSN__CSRRW:
    case RV_INSN__CSRRS:
    case RV_INSN__CSRRC:
    case RV_INSN__CSRRWI:
    case RV_INSN__CSRRSI:
    case RV_INSN__CSRRCI:
      rvtrbk_diagn (state, "unimplemented CSR instructions");
      break;

    /* Synch. insns. */
    case RV_INSN__FENCE:
    case RV_INSN__FENCE_I:
      rvtrbk_diagn (state, "unimplemented synch. instructions");
      break;

    case RV_INSN__INVALID:
      __builtin_unreachable ();
  }
}

#undef _DISPATCH_BINOP_RR