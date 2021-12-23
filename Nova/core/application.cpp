#include "npch.h"
#include "application.h"
#include "platform/platform.h"

namespace Nova {
	Application::Application(const std::string_view& name) : window({ 720, 480 }) {
		Bark::Initialize();
		platform::Initialize(name, window.width, window.height);
	}

	Application::~Application() {
		platform::Termintate();
		Bark::Terminate();
	}

	void Application::execute() {
		running = true;
		try {
			while (running) {
				for (size_t i = 0; i < 10000; ++i) { // temp loop as we can't kill
					render();
					platform::pump_messages();
				}
				running = false;
			}
		} catch (const std::exception& exc) {
			running = false;
			nova_bark_error("Main Execution Exception: {}", exc.what());
			throw;
		}
	}
}
