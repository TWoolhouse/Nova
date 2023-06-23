#pragma once
#include "meta/head.h"
#include "layout.h"
#include "pool.h"
#include "set_update.h"
#include "nvtl/cache.h"

namespace Nova::abyss::nvk::descriptor {

	class NOVAPI Manager {
	public:
		struct LayoutPool {
			Layout layout;
			Pool pool;

			// FIXME: Temporary init values
			LayoutPool(const shader::Layout& layout) : layout(layout), pool(this->layout, Pool::Type::eUniformBuffer, 3) {}
		};
		// TODO: Normal Cache when LayoutPool matures
		nvtl::CacheConstructor<shader::Layout, LayoutPool> cache;
	};

}
