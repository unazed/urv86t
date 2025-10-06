#include "emu.h"
#include "traceback.h"

#define _DISPATCH_BINOP(enum_, op, x, y) \
  case (enum_): state->regs[insn.rd] = x op y; break;
void
rvemu_dispatch (rvstate_t state, insn_t insn)
{
  switch (insn.insn_ty)
  {
    /* Arithmetic/bitwise insns., reg-reg/reg-imm */
    _DISPATCH_BINOP( RV_INSN__ADD, +,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP(RV_INSN__ADDI, +, state->regs[insn.rs1], insn.imm);
    _DISPATCH_BINOP(RV_INSN__SUB, -,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP(RV_INSN__SLL, <<,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP(RV_INSN__SLLI, <<, state->regs[insn.rs1], insn.imm);
    _DISPATCH_BINOP(RV_INSN__SLT, <,
      (iword_t)state->regs[insn.rs1], (iword_t)state->regs[insn.rs2]);
    _DISPATCH_BINOP(RV_INSN__SLTI, <,
      (iword_t)state->regs[insn.rs1], (iword_t)insn.imm);
    _DISPATCH_BINOP(RV_INSN__SLTU, <,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP(RV_INSN__SLTIU, <, state->regs[insn.rs1], insn.imm);
    _DISPATCH_BINOP(RV_INSN__XOR, ^,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP(RV_INSN__XORI, |, state->regs[insn.rs1], insn.imm);
    _DISPATCH_BINOP(RV_INSN__SRL, >>,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP(RV_INSN__SRLI, >>, state->regs[insn.rs1], insn.imm);
    _DISPATCH_BINOP(RV_INSN__SRA, >>,
      (iword_t)state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP(RV_INSN__SRAI, >>,
      (iword_t)state->regs[insn.rs1], insn.imm);
    _DISPATCH_BINOP(RV_INSN__OR, |,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP(RV_INSN__ORI, |, state->regs[insn.rs1], insn.imm);
    _DISPATCH_BINOP(RV_INSN__AND, &,
      state->regs[insn.rs1], state->regs[insn.rs2]);    
    _DISPATCH_BINOP(RV_INSN__ANDI, &, state->regs[insn.rs1], insn.imm);

    /* Load/store insns. */
    case RV_INSN__LB:
      rvtrbk_bndcheck_mem (state, rvmem_reg (state, insn.rs1) + insn.imm);
      *rvmem_regp (state, insn.rd) = (iword_t)(*(i8 *)rvmem_at (
        state, rvmem_reg (state, insn.rs1) + insn.imm)
      );
      break;
    case RV_INSN__LH:
      rvtrbk_bndcheck_mem (state, insn.rs1 + insn.imm);
      *rvmem_regp (state, insn.rd) = (iword_t)(*(i16 *)rvmem_at (
        state, rvmem_reg (state, insn.rs1) + insn.imm))
      ;
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
          state, (hword_t)rvmem_reg (state, insn.rs1) + insn.imm
      );
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
  }
}

#undef _DISPATCH_BINOP_RR