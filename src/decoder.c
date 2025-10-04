#include "decoder.h"
#include "traceback.h"

#define _INSN_CASE(funct, enum_) \
  case (funct): canon_insn.insn_ty = enum_; break;
#define _INSN_OP_CASE(opcode, grp) \
  case (opcode): canon_insn.insn_ty = rvdec_Ity__##grp (insn); break;

static inline enum e_insn
rvdec_Ity__1 (union insn_base insn)
{
  (void)insn;
  return RV_INSN__JALR;
}

static inline enum e_insn
rvdec_Ity__2 (union insn_base insn)
{
  switch (insn.i.funct3)
  {
    case 0b000: return RV_INSN__LB;
    case 0b001: return RV_INSN__LH;
    case 0b010: return RV_INSN__LW;
    /* no 0b011 case */
    case 0b100: return RV_INSN__LBU;
    case 0b101: return RV_INSN__LHU;
    default:
      __builtin_unreachable ();
  }
}

static inline enum e_insn
rvdec_Ity__3 (union insn_base insn)
{
  /* signed arithm. insns. */
  switch (insn.i.funct3)
  {
    case 0b000: return RV_INSN__ADDI;
    case 0b010: return RV_INSN__SLTI;
    case 0b011: return RV_INSN__SLTIU;
    case 0b100: return RV_INSN__XORI;
    case 0b110: return RV_INSN__ORI;
    case 0b111: return RV_INSN__ANDI;
    /* I-format breaks `imm` up for the shift instructions */
    case 0b001:
      if (!insn.x.funct7) 
        return RV_INSN__SLLI;
      break;
    case 0b101:
      if (!insn.x.funct7)
        return RV_INSN__SRLI;
      if (insn.x.funct7 & 0100000)
        return RV_INSN__SRAI;
      __builtin_unreachable ();
      break;
  }
  __builtin_unreachable ();
}

static inline enum e_insn
rvdec_Ity__4 (union insn_base insn)
{
  /* fence/fence.i insns. */
  if (!insn.i.rd && !insn.i.funct3 && !insn.i.rs1
      && (insn.i.imm__11_0 & 0b000011111111))
    return RV_INSN__FENCE;
  if (!insn.i.rd && (insn.i.funct3 & 0b001) && !insn.i.rs1 && !insn.i.imm__11_0)
    return RV_INSN__FENCE_I;
  __builtin_unreachable ();
}

static inline enum e_insn
rvdec_Ity__5 (union insn_base insn)
{
  /* ebreak/ecall csr* insns. */
  if (!insn.i.funct3 && !insn.i.rd && !insn.i.rs1)
  {
    if (!insn.i.imm__11_0)
      return RV_INSN__ECALL;
    if (insn.i.imm__11_0 == 0b000000000001)
      return RV_INSN__EBREAK;
    __builtin_unreachable ();
  }
  switch (insn.i.funct3)
  {
    case 0b001:
      return RV_INSN__CSRRW;
    case 0b010:
      return RV_INSN__CSRRS;
    case 0b011:
      return RV_INSN__CSRRC;
    case 0b101:
      return RV_INSN__CSRRWI;
    case 0b110:
      return RV_INSN__CSRRSI;
    case 0b111:
      return RV_INSN__CSRRCI;
  }
  __builtin_unreachable ();
}

static insn_t
rvdec_Rty (union insn_base insn)
{
  insn_t canon_insn = {
    .rd = insn.r.rd,
    .rs1 = insn.r.rs1,
    .rs2 = insn.r.rs2,
    .funct = (insn.r.funct7 << 3) | insn.r.funct3
  };

  rv_trbk_debug ("\tR-type imm[11:0]: %" PRIi16 "\n", canon_insn.imm);
  
  switch (canon_insn.funct)
  {
    _INSN_CASE(0b0000000000, RV_INSN__ADD);
    _INSN_CASE(0b0100000000, RV_INSN__SUB);
    _INSN_CASE(0b0000000001, RV_INSN__SLL);
    _INSN_CASE(0b0000000010, RV_INSN__SLT);
    _INSN_CASE(0b0000000011, RV_INSN__SLTU);
    _INSN_CASE(0b0000000100, RV_INSN__XOR);
    _INSN_CASE(0b0000000101, RV_INSN__SRL);
    _INSN_CASE(0b0100000101, RV_INSN__SRA);
    _INSN_CASE(0b0000000110, RV_INSN__OR);
    _INSN_CASE(0b0000000111, RV_INSN__AND);
  }

  return canon_insn;
}

static insn_t
rvdec_Ity (union insn_base insn)
{
  insn_t canon_insn = {
    .rd = insn.i.rd,
    .rs1 = insn.i.rs1,
    .funct = insn.i.funct3,
    .imm = SIGNEXT(insn.i.imm__11_0, 1 << 11)
  };

  switch (insn.i.opcode)
  {
    /* I-format insns. have 5 groupings of opcodes */
    _INSN_OP_CASE(0b1100111, 1);
    _INSN_OP_CASE(0b0000011, 2);
    _INSN_OP_CASE(0b0010011, 3);
    _INSN_OP_CASE(0b0001111, 4);
    _INSN_OP_CASE(0b1110011, 5);
  }

  rv_trbk_debug (
    "\tI-type %s %s, %s, %" PRIi16 "\n",
    repr_insn_map[canon_insn.insn_ty],
    repr_reg_abi_map[canon_insn.rd], repr_reg_abi_map[canon_insn.rs1],
    canon_insn.imm
  );

  return canon_insn;
}

static insn_t
rvdec_Sty (union insn_base insn)
{
  insn_t canon_insn = {
    .rs1 = insn.s.rs1,
    .rs2 = insn.s.rs2,
    .funct = insn.s.funct3,
    .imm = SIGNEXT((insn.s.imm__11_5 << 5) | insn.s.imm__4_0, 1 << 11)
  };

  switch (canon_insn.funct)
  {
    _INSN_CASE(0b000, RV_INSN__SB);
    _INSN_CASE(0b001, RV_INSN__SH);
    _INSN_CASE(0b010, RV_INSN__SW);
  }

  rv_trbk_debug (
    "\tS-type %s rs1=%" PRIu8 " rs2=%" PRIu8 " imm=%" PRIi16 "\n",
    repr_insn_map[canon_insn.insn_ty], canon_insn.rs1, canon_insn.rs2,
    canon_insn.imm
  );

  return canon_insn;
}

static insn_t
rvdec_Uty (union insn_base insn)
{
  insn_t canon_insn = {
    .rd = insn.u.rd,
    .imm = insn.u.imm__31_12 << 12
  };

  switch (insn.u.opcode)
  {
    _INSN_CASE(0b0110111, RV_INSN__LUI);
    _INSN_CASE(0b0010111, RV_INSN__AUIPC);
  }

  return canon_insn;
}

static insn_t
rvdec_Jty (union insn_base insn)
{
  insn_t canon_insn = {
    .rd = insn.j.rd,
    .imm = SIGNEXT(
      (insn.j.imm__20 << 20)
        | (insn.j.imm__19_12 << 12)
        | (insn.j.imm__11 << 11)
        | (insn.j.imm__10_1 << 1),
      1 << 20
    )
  };

  switch (insn.u.opcode)
  {
    _INSN_CASE(0b0110111, RV_INSN__LUI);
    _INSN_CASE(0b0010111, RV_INSN__AUIPC);
  }

  return canon_insn;
}

static insn_t
rvdec_Bty (union insn_base insn)
{
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

  switch (insn.b.funct3)
  {
    _INSN_CASE(0b000, RV_INSN__BEQ);
    _INSN_CASE(0b001, RV_INSN__BNE);
    _INSN_CASE(0b100, RV_INSN__BLT);
    _INSN_CASE(0b101, RV_INSN__BGE);
    _INSN_CASE(0b110, RV_INSN__BLTU);
    _INSN_CASE(0b111, RV_INSN__BGEU);
  }

  return canon_insn;
}

#undef _INSN_CASE
#undef _INSN_OP_CASE

insn_t
rvdec_insn (word_t bytes)
{
  auto as_base = (union insn_base)bytes;
  if (RISCV_INSN_OPCOND__R(as_base.x.opcode))
  {
    rv_trbk_debug ("decoding R-format insn. (%08" PRIx32 ")\n", bytes);
    return rvdec_Rty (as_base);
  }
  else if (RISCV_INSN_OPCOND__I(as_base.x.opcode))
  {
    rv_trbk_debug ("decoding I-format insn. (%08" PRIx32 ")\n", bytes);
    return rvdec_Ity (as_base);
  }
  else if (RISCV_INSN_OPCOND__S(as_base.x.opcode))
  {
    rv_trbk_debug ("decoding S-format insn. (%08" PRIx32 ")\n", bytes);
    return rvdec_Sty (as_base);
  }
  else if (RISCV_INSN_OPCOND__U(as_base.x.opcode))
  {
    rv_trbk_debug ("decoding U-format insn. (%08" PRIx32 ")\n", bytes);
    return rvdec_Uty (as_base);
  }
  else if (RISCV_INSN_OPCOND__J(as_base.x.opcode))
  {
    rv_trbk_debug ("decoding J-format insn. (%08" PRIx32 ")\n", bytes);
    return rvdec_Jty (as_base);
  }
  else if (RISCV_INSN_OPCOND__B(as_base.x.opcode))
  {
    rv_trbk_debug ("decoding B-format insn. (%08" PRIx32 ")\n", bytes);
    return rvdec_Bty (as_base);
  }
  __builtin_unreachable ();
}