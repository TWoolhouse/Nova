#include "npch.h"
#include "meta/head.h"

// Includes Here
#include "abyss/nvk/descriptor/manager.h"
#include "abyss/nvk/descriptor/set_update.h"
#include "abyss/shader.h"

namespace Nova {

	struct UniformA {
		int x;
	};

	void test() {
		nova_bark_debug("Test...");

		{
			// Code Here
			constexpr blip::Unit dur{ 10.50 };
			constexpr auto x = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
		}

		nova_bark_debug("Test!");
	}

}
