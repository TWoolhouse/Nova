#include "npch.h"
#include "application.h"

namespace Nova {
	Application::Application(const std::string_view& name) {
		Bark::Initialize();
	}

	Application::~Application() {
		Bark::Terminate();
	}
}
