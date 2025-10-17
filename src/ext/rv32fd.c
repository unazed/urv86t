#include "emu.h"
#include "ext/rv32fd.h"

freg_t
rvfloat_nanbox_saturate (u32 val)
{
  return (u64)val | 0xffffffff00000000ull;
}

freg_t
rvfloat_nanbox_unpack (u64 val)
{
  return (u32)(val & 0xffffffff);
}

f64
rvfloat_as_f64 (u64 val)
{
  return *(f64 *)&val;
}

u64
rvfloat_as_u64(f64 val)
{
  return *(u64 *)&val;
}

f32
rvfloat_as_f32 (u32 val)
{
  return *(f32 *)&val;
}

u32
rvfloat_as_u32 (f32 val)
{
  return *(u32 *)&val;
}

f32
rvfloat_read_f32 (rvstate_t state, u8 freg)
{
  return rvfloat_as_f32 (rvfloat_nanbox_unpack (rvmem_freg (state, freg)));
}

f64
rvfloat_read_f64 (rvstate_t state, u8 freg)
{
  return rvfloat_as_f64 (rvmem_freg (state, freg));
}

void
rvfloat_write_f32 (rvstate_t state, u8 freg, f32 val)
{
  *rvmem_fregp (state, freg) = rvfloat_nanbox_saturate (rvfloat_as_u32 (val));
}

void
rvfloat_write_f64 (rvstate_t state, u8 freg, f64 val)
{
  *rvmem_fregp (state, freg) = rvfloat_as_u64 (val);
}

void
rvfloat_cvt_f32_from_i32 (rvstate_t state, u8 freg, i32 val)
{
  rvfloat_write_f32 (state, freg, (f32)val);
}

void
rvfloat_cvt_f32_from_u32 (rvstate_t state, u8 freg, u32 val)
{
  rvfloat_write_f32 (state, freg, (f32)val);
}

void
rvfloat_cvt_f64_from_i32 (rvstate_t state, u8 freg, i32 val)
{
  rvfloat_write_f64 (state, freg, (f64)val);
}

void
rvfloat_cvt_f64_from_u32 (rvstate_t state, u8 freg, u32 val)
{
  rvfloat_write_f64 (state, freg, (f64)val);
}