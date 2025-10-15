#include "insn/formats.h"

enum e_insn
rvdec_Rty__1 (rvstate_t state, union insn_base insn)
{
  (void)state;
  switch ((insn.r.funct7 << 3) | insn.r.funct3)
  {
    INSN_CASE_RET(0b0000000000, RV_INSN__ADD);
    INSN_CASE_RET(0b0100000000, RV_INSN__SUB);
    INSN_CASE_RET(0b0000000001, RV_INSN__SLL);
    INSN_CASE_RET(0b0000000010, RV_INSN__SLT);
    INSN_CASE_RET(0b0000000011, RV_INSN__SLTU);
    INSN_CASE_RET(0b0000000100, RV_INSN__XOR);
    INSN_CASE_RET(0b0000000101, RV_INSN__SRL);
    INSN_CASE_RET(0b0100000101, RV_INSN__SRA);
    INSN_CASE_RET(0b0000000110, RV_INSN__OR);
    INSN_CASE_RET(0b0000000111, RV_INSN__AND);
#if RV32_HAS(EXT_M)
    INSN_CASE_RET(0b0000001000, RV_INSN__MUL);
    INSN_CASE_RET(0b0000001001, RV_INSN__MULH)
    INSN_CASE_RET(0b0000001010, RV_INSN__MULHSU);
    INSN_CASE_RET(0b0000001011, RV_INSN__MULHU);
    INSN_CASE_RET(0b0000001100, RV_INSN__DIV);
    INSN_CASE_RET(0b0000001101, RV_INSN__DIVU);
    INSN_CASE_RET(0b0000001110, RV_INSN__REM);
    INSN_CASE_RET(0b0000001111, RV_INSN__REMU);
#endif
  }
  return RV_INSN__INVALID;
}

#if RV32_HAS(EXT_FD)
enum e_insn
rvdec_Rty__2 (rvstate_t state, union insn_base insn)
{
  (void)state; (void)insn;
  return RV_INSN__INVALID;
}
#endif

insn_t
rvdec_Rty (rvstate_t state, union insn_base insn)
{
  (void)state;
  insn_t canon_insn = {
    .rd = insn.r.rd,
    .rs1 = insn.r.rs1,
    .rs2 = insn.r.rs2,
    .funct = (insn.r.funct7 << 3) | insn.r.funct3
  };

  switch (insn.r.opcode)
  {
    INSN_OP_CASE(RISCV_INSN_R__REG,   R, 1);
#if RV32_HAS(EXT_FD)
    INSN_OP_CASE(RISCV_INSN_R__FLOAT, R, 2);
#endif
  }

  rvtrbk_debug (
    "\tR-type %s %s, %s, %s\n",
    repr_insn_map[canon_insn.insn_ty],
    repr_reg_abi_map[canon_insn.rd], repr_reg_abi_map[canon_insn.rs1],
    repr_reg_abi_map[canon_insn.rs2]
  );

  return canon_insn;
}

#if RV32_HAS(EXT_FD)
insn_t
rvdec_R4ty (rvstate_t state, union insn_base insn)
{
  (void)state;
  insn_t canon_insn = {
    .rs1 = insn.b.rs1,
    .rs2 = insn.b.rs2,
    .funct = insn.b.funct3,
    .imm = SIGNEXT(
      (insn.b.imm__12 << 12)
        | (insn.b.imm__11 << 11)
        | (insn.b.imm__10_5 << 5)
        | (insn.b.imm__4_1 << 1),
      1 << 12
    )
  };

  return canon_insn;
}
#endif