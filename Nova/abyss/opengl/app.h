#pragma once
#include "meta/head.h"

namespace Nova::abyss::gl {

	class Application {
	public:
		static Application* I;
		bool active;
		
		Application(const std::string_view& name);
		~Application();

		bool& acquire();
		void  release();

	};

}

#define App ::Nova::abyss::gl::Application::I