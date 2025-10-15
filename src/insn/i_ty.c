#include "insn/formats.h"

enum e_insn
rvdec_Ity__1 (rvstate_t state, union insn_base insn)
{
  (void)state; (void)insn;
  return RV_INSN__JALR;
}

enum e_insn
rvdec_Ity__2 (rvstate_t state, union insn_base insn)
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
      rvtrbk_diagn (state, "unrecognised LOAD insn. function bits");
      return RV_INSN__INVALID;
  }
}

enum e_insn
rvdec_Ity__3 (rvstate_t state, union insn_base insn)
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
      if (insn.x.funct7 == 0b0100000)
        return RV_INSN__SRAI;
      rvtrbk_diagn (state, "unrecognised shift insn. function bits");
      return RV_INSN__INVALID;
  }
  __builtin_unreachable ();
}

enum e_insn
rvdec_Ity__4 (rvstate_t state, union insn_base insn)
{
  /* fence/fence.i insns. */
  if (!insn.i.rd && !insn.i.funct3 && !insn.i.rs1
      && (insn.i.imm__11_0 == 0b000011111111))
    return RV_INSN__FENCE;
  if (!insn.i.rd && (insn.i.funct3 == 0b001) && !insn.i.rs1
      && !insn.i.imm__11_0)
    return RV_INSN__FENCE_I;
  rvtrbk_diagn (state, "unrecognised synch. instruction");
  return RV_INSN__INVALID;
}

enum e_insn
rvdec_Ity__5 (rvstate_t state, union insn_base insn)
{
  /* ebreak/ecall csr* insns. */
  if (!insn.i.funct3 && !insn.i.rd && !insn.i.rs1)
  {
    if (!insn.i.imm__11_0)
      return RV_INSN__ECALL;
    if (insn.i.imm__11_0 == 0b000000000001)
      return RV_INSN__EBREAK;
    rvtrbk_diagn (state, "unrecognised environment insn. immediate specifier");
    return RV_INSN__INVALID;
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
    default:
      rvtrbk_diagn (state, "unrecognised environment insn. function bits");
      return RV_INSN__INVALID;
  }
}

#if RV32_HAS(EXT_FD)
enum e_insn
rvdec_Ity__6 (rvstate_t state, union insn_base insn)
{
  switch (insn.i.funct3)
  {
    case RISCV_FLTFUNC_SINGLE:
    case RISCV_FLTFUNC_DOUBLE:
      return RV_INSN__FLx;
    default:
      rvtrbk_diagn (state, "unrecognised float-load function bits");
      return RV_INSN__INVALID;
  }
}
#endif

insn_t
rvdec_Ity (rvstate_t state, union insn_base insn)
{
  insn_t canon_insn = {
    .rd = insn.i.rd,
    .rs1 = insn.i.rs1,
    .funct = insn.i.funct3,
    .imm = SIGNEXT(insn.i.imm__11_0, 1 << 11)
  };

  switch (insn.i.opcode)
  {
    /* I-format insns. have 5 base opcode groupings */
    INSN_OP_CASE(RISCV_INSN_I__JALR,  I, 1);
    INSN_OP_CASE(RISCV_INSN_I__LOAD,  I, 2);
    INSN_OP_CASE(RISCV_INSN_I__ARITH, I, 3);
    INSN_OP_CASE(RISCV_INSN_I__SYNCH, I, 4);
    INSN_OP_CASE(RISCV_INSN_I__ENV,   I, 5);
#if RV32_HAS(EXT_FD)
    INSN_OP_CASE(RISCV_INSN_I__FLOAT, I, 6);
#endif
  }

  if (canon_insn.insn_ty != RV_INSN__INVALID)
  {
    rvtrbk_debug (
      "\tI-type %s %s, %s, %" PRIi16 "\n",
      repr_insn_map[canon_insn.insn_ty],
      repr_reg_abi_map[canon_insn.rd], repr_reg_abi_map[canon_insn.rs1],
      canon_insn.imm
    );
  }

  return canon_insn;
}