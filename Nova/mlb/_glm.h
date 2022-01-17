#include "meta/head.h"

#define GLM_FORCE_INLINE
#define GLM_FORCE_SWIZZLE

#ifdef NOVA_DEBUG
	//#define GLM_FORCE_MESSAGES
	#define GLM_FORCE_PURE
#else // !NOVA_DEBUG
	#define GLM_FORCE_INTRINSICS
	#define GLM_FORCE_ALIGNED
#endif // NOVA_DEBUG

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Nova::mlb {
	using namespace ::glm;
}