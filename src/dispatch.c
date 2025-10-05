#include "emu.h"

#define _DISPATCH_BINOP_RR(enum_, op, x, y) \
  case (enum_): state->regs[insn.rd] = x op y; break;

void
rvemu_dispatch (rvstate_t state, insn_t insn)
{
  switch (insn.insn_ty)
  {
    _DISPATCH_BINOP_RR(RV_INSN__ADD, +,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP_RR(RV_INSN__SUB, -,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP_RR(RV_INSN__SLL, <<,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP_RR(RV_INSN__SLT, <,
      (iword_t)state->regs[insn.rs1], (iword_t)state->regs[insn.rs2]);
    _DISPATCH_BINOP_RR(RV_INSN__SLTU, <,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP_RR(RV_INSN__XOR, ^,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP_RR(RV_INSN__SRL, >>,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP_RR(RV_INSN__SRA, >>,
      (iword_t)state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP_RR(RV_INSN__OR, |,
      state->regs[insn.rs1], state->regs[insn.rs2]);
    _DISPATCH_BINOP_RR(RV_INSN__AND, &,
      state->regs[insn.rs1], state->regs[insn.rs2]);
  }
}

#undef _DISPATCH_BINOP_RR