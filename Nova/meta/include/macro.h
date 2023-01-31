#pragma once
#include "defines.h"

#define _N_OVA_MC_CONCAT(x, y) x##y
#define NOVA_MC_CONCAT(x, y) _N_OVA_MC_CONCAT(x, y)

#define _N_OVA_MC_STRINGIFY(x) #x
#define NOVA_MC_STRINGIFY(x) _N_OVA_MC_STRINGIFY(x)

#define NOVA_MC_UNUSED(x) (void)(x)

#ifdef NOVA_DEBUG
#define nova_debug_exc(expr) expr
#else // !NOVA_DEBUG
#define nova_debug_exc(expr)
#endif // NOVA_DEBUG
