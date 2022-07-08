#include "npch.h"
#include "meta/head.h"

#include "nvtl/weave.h"

void t() {
	using namespace Nova;
	nova_bark_debug("Test...");

	constexpr auto threads = 2;
	nvtl::Weave<std::function<bool(int)>, threads> weave;
	auto ticket = weave.push_back(0, [](auto x) { nova_bark_warn("OMG: {}", x); return false; });
	weave.push_back(0, [](auto x) { nova_bark_warn("OMG 1: {}", x); return false; });
	weave.push_back(1, [](auto x) { nova_bark_warn("OMG 2: {}", x); return false; });
	weave.push_back(0, [](auto x) { nova_bark_warn("OMG 3: {}", x); return false; });
	weave.push_back(1, [](auto x) { nova_bark_warn("OMG 4: {}", x); return false; });
	weave.push_back(0, [](auto x) { nova_bark_warn("OMG 5: {}", x); return false; });
	weave.push_back(1, [](auto x) { nova_bark_warn("OMG 6: {}", x); return false; });
	weave.push_back(0, [](auto x) { nova_bark_warn("OMG 7: {}", x); return false; });
	weave.push_back(1, [](auto x) { nova_bark_warn("OMG 8: {}", x); return false; });

	for (auto&& thread : weave) {
		for (auto&& func : thread) {
			func(0);
		}
	}

	weave.remove(ticket);

	for (auto&& thread : weave) {
		for (auto&& func : thread) {
			func(0);
		}
	}

	nova_bark_debug("Test!");
}
