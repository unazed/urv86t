#include "insn/formats.h"

static inline struct insn_ty_argspec_pair
rvdec_Ity__1 (rvstate_t state, union insn_base insn)
{
  (void)state; (void)insn;
  return MAKE_INSN(RV_INSN__JALR, RV_ARGSPEC__R32_R32_pcrel);
}

static inline struct insn_ty_argspec_pair
rvdec_Ity__2 (rvstate_t state, union insn_base insn)
{
  switch (insn.i.funct3)
  {
    INSN_CASE_RET(0b000, RV_INSN__LB, RV_ARGSPEC__R32_m8_offs);
    INSN_CASE_RET(0b001, RV_INSN__LH, RV_ARGSPEC__R32_m16_offs);
    INSN_CASE_RET(0b010, RV_INSN__LW, RV_ARGSPEC__R32_m32_offs);
    /* no 0b011 case */
    INSN_CASE_RET(0b100, RV_INSN__LBU, RV_ARGSPEC__R32_m8u_offs);
    INSN_CASE_RET(0b101, RV_INSN__LHU, RV_ARGSPEC__R32_m16u_offs);
    default:
      rvtrbk_diagn (state, "unrecognised LOAD insn. function bits");
      return INVALID_INSN;
  }
}

static inline struct insn_ty_argspec_pair
rvdec_Ity__3 (rvstate_t state, union insn_base insn)
{
  switch (insn.i.funct3)
  {
    INSN_CASE_RET(0b000, RV_INSN__ADDI, RV_ARGSPEC__R32_R32_i12);
    INSN_CASE_RET(0b010, RV_INSN__SLTI, RV_ARGSPEC__R32_R32_i12);
    INSN_CASE_RET(0b011, RV_INSN__SLTIU, RV_ARGSPEC__R32_R32_u12);
    INSN_CASE_RET(0b100, RV_INSN__XORI, RV_ARGSPEC__R32_R32_u12);
    INSN_CASE_RET(0b110, RV_INSN__ORI, RV_ARGSPEC__R32_R32_u12);
    INSN_CASE_RET(0b111, RV_INSN__ANDI, RV_ARGSPEC__R32_R32_u12);

    /* I-format breaks `imm` up for the shift instructions */
    case 0b001:
      if (!insn.x.funct7)
        return MAKE_INSN(RV_INSN__SLLI, RV_ARGSPEC__R32_R32_u5);
      break;
    case 0b101:
      if (!insn.x.funct7)
        return MAKE_INSN(RV_INSN__SRLI, RV_ARGSPEC__R32_R32_u5);
      if (insn.x.funct7 == 0b0100000)
        return MAKE_INSN(RV_INSN__SRAI, RV_ARGSPEC__R32_R32_u5);
      rvtrbk_diagn (state, "unrecognised shift insn. function bits");
      return INVALID_INSN;
  }
  __builtin_unreachable ();
}

static inline struct insn_ty_argspec_pair
rvdec_Ity__4 (rvstate_t state, union insn_base insn)
{
  if (!insn.i.rd && !insn.i.funct3 && !insn.i.rs1
      && (insn.i.imm__11_0 == 0b000011111111))
    return MAKE_INSN(RV_INSN__FENCE, RV_ARGSPEC__NONE);
  if (!insn.i.rd && (insn.i.funct3 == 0b001) && !insn.i.rs1
      && !insn.i.imm__11_0)
    return MAKE_INSN(RV_INSN__FENCE_I, RV_ARGSPEC__NONE);
  rvtrbk_diagn (state, "unrecognised synch. instruction");
  return INVALID_INSN;
}

static inline struct insn_ty_argspec_pair
rvdec_Ity__5 (rvstate_t state, union insn_base insn)
{
  if (!insn.i.funct3 && !insn.i.rd && !insn.i.rs1)
  {
    if (!insn.i.imm__11_0)
      return MAKE_INSN(RV_INSN__ECALL, RV_ARGSPEC__NONE);
    if (insn.i.imm__11_0 == 0b000000000001)
      return MAKE_INSN(RV_INSN__EBREAK, RV_ARGSPEC__NONE);
    rvtrbk_diagn (state, "unrecognised environment insn. immediate specifier");
    return INVALID_INSN;
  }
  switch (insn.i.funct3)
  {
    INSN_CASE_RET(0b001, RV_INSN__CSRRW, RV_ARGSPEC__R32_csr_R32);
    INSN_CASE_RET(0b010, RV_INSN__CSRRS, RV_ARGSPEC__R32_csr_R32);
    INSN_CASE_RET(0b011, RV_INSN__CSRRC, RV_ARGSPEC__R32_csr_R32);
    INSN_CASE_RET(0b101, RV_INSN__CSRRWI, RV_ARGSPEC__R32_csr_u5);
    INSN_CASE_RET(0b110, RV_INSN__CSRRSI, RV_ARGSPEC__R32_csr_u5);
    INSN_CASE_RET(0b111, RV_INSN__CSRRCI, RV_ARGSPEC__R32_csr_u5);
    default:
      rvtrbk_diagn (state, "unrecognised environment insn. function bits");
      return INVALID_INSN;
  }
}

#if RV32_HAS(EXT_FD)
static inline struct insn_ty_argspec_pair
rvdec_Ity__6 (rvstate_t state, union insn_base insn)
{
  switch (insn.i.funct3)
  {
    case RISCV_FLTFUNC_SINGLE:
    case RISCV_FLTFUNC_DOUBLE:
      return MAKE_INSN(RV_INSN__FLx, RV_ARGSPEC__Fx_mX_offs);
    default:
      rvtrbk_diagn (state, "unrecognised float-load function bits");
      return INVALID_INSN;
  }
}
#endif

insn_t
rvdec_Ity (rvstate_t state, union insn_base insn)
{
  struct insn_argspec_pair pair = {
    .insn = {
      .rd = insn.i.rd,
      .rs1 = insn.i.rs1,
      .funct = insn.i.funct3,
      .imm = SIGNEXT(insn.i.imm__11_0, 1 << 11)
    }
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

  rvasm_emit (state, pair);
  return pair.insn;
}