#include "npch.h"
#include "application.h"
#include "platform/platform.h"
#include "event/window.h"

namespace Nova {
	Application::Application(const std::string_view& name) : window({ 720, 480 }) {
		Bark::Initialize();
		platform::Initialize(name, window.width, window.height);
		event::Register(event::Type::WindowClose, [this](event::Base&) -> bool { this->terminate(); return true; });
	}

	Application::~Application() {
		platform::Termintate();
		Bark::Terminate();
	}

	void Application::execute() {
		running = true;
		try {
			while (running) {
				render();
				platform::pump_messages();
			}
		} catch (const std::exception& exc) {
			running = false;
			nova_bark_error("Main Execution Exception: {}", exc.what());
			throw;
		}
	}
}
