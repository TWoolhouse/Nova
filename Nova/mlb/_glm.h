#include "meta/head.h"

#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_FORCE_UNRESTRICTED_GENTYPE

#define GLM_FORCE_INLINE

#ifdef NOVA_DEBUG
	//#define GLM_FORCE_MESSAGES
	#define GLM_FORCE_PURE
#else // !NOVA_DEBUG
	#define GLM_FORCE_INTRINSICS
	#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#endif // NOVA_DEBUG

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Nova::mlb {
	using namespace ::glm;
}
