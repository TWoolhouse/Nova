#pragma once
#include "meta/head.h"
#include "vk.h"

namespace Nova::abyss::nvk {

	struct Semaphore : public OPVK<Semaphore, vk::Semaphore> {
		vk::Semaphore self;
		Semaphore();
		~Semaphore();
	};
	struct Fence : public OPVK<Fence, vk::Fence> {
		vk::Fence self;
		Fence();
		Fence(bool signal);
		~Fence();
	};

}
