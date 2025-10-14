#pragma once

#define __RV32_FEATURES__
#define RV32_HAS(x) RV32_FEATURE_##x

/* Multiplication/division extension */
#ifndef RV32_FEATURE_EXT_M
# define RV32_FEATURE_EXT_M (1)
#endif

/* Compressed instructions */
#ifndef RV32_FEATURE_EXT_C
# define RV32_FEATURE_EXT_C (1)
#endif

/* Single/double floating-point */
#ifndef RV32_FEATURE_EXT_FD
# define RV32_FEATURE_EXT_FD (1)
#endif

#ifndef RV32_FEATURE_BKPT
# define RV32_FEATURE_BKPT (1)
#endif