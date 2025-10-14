#pragma once

/* Feature inclusions for headers that have circular dependencies
 * on `emu.h`/`platform.h`, included later in the definitions to provide
 * symbol definitions for non-opaque type definitions
 */

#ifndef __RV32_FEATURES__
# error "feature.h must be included prior to feature-dep.h"
#endif

#if RV32_HAS(BKPT)
# include "bkpt.h"
#endif