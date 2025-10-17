#pragma once

/* Feature inclusions for headers that have no circular dependencies
 * on `emu.h`/`platform.h`
 */

#ifndef __RV32_FEATURES__
# error "feature.h must be included prior to feature-nodep.h"
#endif

#if RV32_HAS(EXT_M)
# include "ext/rv32m.h"
#endif

#if RV32_HAS(EXT_C)
# include "ext/rv32c.h"
#endif

#if RV32_HAS(EXT_FD)
# include "ext/rv32fd.h"
#endif