#pragma once
#include "bark/bark.h"

namespace Nova::meta {

	struct Test {
		int x;
		Test() : x(0) {
			nova_bark_debug("Constructor Default");
		}
		Test(const int x) : x(x) {
			nova_bark_debug("Constructor {}", x);
		}
		Test(const Test& other) : x(other.x) {
			nova_bark_debug("Copy Constructor {}", x);
		}
		Test& operator=(const Test& other) {
			x = other.x; nova_bark_debug("Copy Assignment {}", x); return *this;
		}
		Test(Test&& other) : x(std::move(other.x)) {
			other.x = 0; nova_bark_debug("Move Contstructor {}", x);
		}
		Test& operator=(Test&& other) {
			x = std::move(other.x); other.x = 0; nova_bark_debug("Move Assignmet {}", x); return *this;
		}
		~Test() {
			nova_bark_debug("Destructor {}", x);
		}
	};

}
