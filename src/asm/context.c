#include <stdlib.h>

#include "traceback.h"
#include "insn/formats.h"
#include "asm/context.h"

#if RV32_HAS(EXT_FD)
# define FREG(reg) (repr_freg_abi_map[reg])
#endif
#define REG(reg) (repr_reg_abi_map[reg])
#define INSN(insn) (repr_insn_map[insn])

void
rvasm_emit (rvstate_t state, struct insn_argspec_pair pair)
{
  (void)state;
  auto insn = pair.insn;
  auto argspec = pair.argspec;

  switch (argspec)
  {
    case RV_ARGSPEC__NONE:
      rvtrbk_verbose ("%s\n", repr_insn_map[insn.insn_ty]);
      break;
    case RV_ARGSPEC__R32_R32_R32:
      rvtrbk_verbose (
        "%s %s, %s, %s\n",
        INSN(insn.insn_ty), REG(insn.rd), REG(insn.rs1), REG(insn.rs2));
      break;
    case RV_ARGSPEC__R32_R32_i12:
      rvtrbk_verbose (
        "%s %s, %s, %" PRIi32 "\n",
        INSN(insn.insn_ty), REG(insn.rd), REG(insn.rs1), insn.imm);
      break;
    case RV_ARGSPEC__R32_R32_u12:
      rvtrbk_verbose (
        "%s %s, %s, %" PRIu32 "\n",
        INSN(insn.insn_ty), REG(insn.rd), REG(insn.rs1), insn.imm);
      break;
    case RV_ARGSPEC__R32_R32_u5:
      rvtrbk_verbose (
        "%s %s, %s, %" PRIu32 "\n",
        INSN(insn.insn_ty), REG(insn.rd), REG(insn.rs1), insn.imm);
      break;
    case RV_ARGSPEC__R32_m8_offs:
      rvtrbk_verbose (
        "%s %s, %" PRIi32 "(%s).b\n",
        INSN(insn.insn_ty), REG(insn.rd), insn.imm, REG(insn.rs1));
      break;
    case RV_ARGSPEC__R32_m8u_offs:
      rvtrbk_verbose (
        "%s %s, %" PRIi32 "(%s).bu\n",
        INSN(insn.insn_ty), REG(insn.rd), insn.imm, REG(insn.rs1));
      break;
    case RV_ARGSPEC__R32_m16_offs:
      rvtrbk_verbose (
        "%s %s, %" PRIi32 "(%s).hw\n",
        INSN(insn.insn_ty), REG(insn.rd), insn.imm, REG(insn.rs1));
      break;
    case RV_ARGSPEC__R32_m16u_offs:
      rvtrbk_verbose (
        "%s %s, %" PRIi32 "(%s).hwu\n",
        INSN(insn.insn_ty), REG(insn.rd), insn.imm, REG(insn.rs1));
      break;
    case RV_ARGSPEC__R32_m32_offs:
      rvtrbk_verbose (
        "%s %s, %" PRIi32 "(%s)\n",
        INSN(insn.insn_ty), REG(insn.rd), insn.imm, REG(insn.rs1));
      break;
    case RV_ARGSPEC__m8_offs_R32:
      rvtrbk_verbose (
        "%s %" PRIi32 "(%s).b, %s\n",
        INSN(insn.insn_ty), insn.imm, REG(insn.rs1), REG(insn.rd));
      break;
    case RV_ARGSPEC__m16_offs_R32:
      rvtrbk_verbose (
        "%s %" PRIi32 "(%s).hw, %s\n",
        INSN(insn.insn_ty), insn.imm, REG(insn.rs1), REG(insn.rd));
      break;
    case RV_ARGSPEC__m32_offs_R32:
      rvtrbk_verbose (
        "%s %" PRIi32 "(%s), %s\n",
        INSN(insn.insn_ty), insn.imm, REG(insn.rs1), REG(insn.rd));
      break;
    case RV_ARGSPEC__R32_R32_pcrel:
    case RV_ARGSPEC__R32_R32_pcrelu:
      rvtrbk_verbose (
        "%s %s, %s, %" PRIi32 "\n",
        INSN(insn.insn_ty), REG(insn.rs1), REG(insn.rs2), insn.imm);
      break;
    case RV_ARGSPEC__R32_pcrel:
      rvtrbk_verbose (
        "%s %s, %" PRIi32 "\n",
        INSN(insn.insn_ty), REG(insn.rd), insn.imm);
      break;
    case RV_ARGSPEC__R32_u20:
      rvtrbk_verbose (
        "%s %s, %" PRIi32 "\n",
        INSN(insn.insn_ty), REG(insn.rd), insn.imm);
      break;
    case RV_ARGSPEC__R32_csr_R32:
    case RV_ARGSPEC__R32_csr_u5:
      rvtrbk_fatal ("unsupported CSR representation\n");  
      break;

#if RV32_HAS(EXT_FD)
    /* TODO: Convert insn. representations to show proper F/D types in place
     *       of the `x` placeholders
     */
    case RV_ARGSPEC__Fx_Fx_Fx:
      rvtrbk_verbose (
        "%s %s, %s, %s\n",
        INSN(insn.insn_ty), FREG(insn.rd), FREG(insn.rs1), FREG(insn.rs2));
      break;
    case RV_ARGSPEC__Fx_Fx_Fx_Fx:
      rvtrbk_verbose (
        "%s %s, %s, %s, %s\n",
        INSN(insn.insn_ty), FREG(insn.rd), FREG(insn.rs1), FREG(insn.rs2),
        FREG(insn.rs3));
      break;
    case RV_ARGSPEC__Fx_Fx:
      rvtrbk_verbose (
        "%s %s, %s\n",
        INSN(insn.insn_ty), FREG(insn.rd), FREG(insn.rs1));
      break;
    case RV_ARGSPEC__Fx_mX_offs:
      rvtrbk_verbose (
        "%s %s, %" PRIi32 "(%s)\n",
        INSN(insn.insn_ty), FREG(insn.rd), insn.imm, FREG(insn.rs1));
      break;
    case RV_ARGSPEC__mX_offs_Fx:
      rvtrbk_verbose (
        "%s %" PRIi32 "(%s), %s\n",
        INSN(insn.insn_ty), insn.imm, REG(insn.rs1), FREG(insn.rs2));
      break;
    case RV_ARGSPEC__R32_Fx_Fx:
      rvtrbk_verbose (
        "%s %s, %s, %s\n",
        INSN(insn.insn_ty), REG(insn.rd), FREG(insn.rs1), FREG(insn.rs2));
      break;
    case RV_ARGSPEC__R32_Fx:
      rvtrbk_verbose (
        "%s %s, %s\n",
        INSN(insn.insn_ty), REG(insn.rd), FREG(insn.rs1));
      break;
    case RV_ARGSPEC__Fx_R32:
      rvtrbk_verbose (
        "%s %s, %s\n",
        INSN(insn.insn_ty), FREG(insn.rd), REG(insn.rs1));
      break;
    case RV_ARGSPEC__Fx_Fx_cvt:
      rvtrbk_verbose (
        "%s %s, %s\n",
        INSN(insn.insn_ty), FREG(insn.rd), FREG(insn.rs1));
      break;
#endif

    default:
      rvtrbk_fatal ("unimplemented argspec for emitting\n");
      break;
  }
}

rvasm_ctx_t
rvasm_init (const char* const path)
{
  rvasm_ctx_t ctx = calloc (1, sizeof (struct rvasm_ctx));
  if (ctx == NULL)
    rvtrbk_fatal ("failed to allocate RVASM context\n");
  auto out_fd = fopen (path, "w");
  if (out_fd == NULL)
  {
    free (ctx);
    return NULL;
  }
  ctx->out_fd = out_fd;
  return ctx;
}

void
rvasm_free (rvasm_ctx_t ctx)
{
  fclose (ctx->out_fd);
  free (ctx);
}