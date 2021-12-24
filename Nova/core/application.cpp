#include "npch.h"
#include "application.h"
#include "platform/platform.h"
#include "event/window.h"

namespace Nova {
	Application::Application(const std::string_view& name) : window({ 720, 480 }) {
		Bark::Initialize();
		platform::Initialize(name, window.width, window.height);
		
		// Events
		event::Register(event::Type::WindowClose, [this](event::Base&)->bool { this->terminate(); return false; });
		event::Register(event::Type::WindowResizeScreen, [this](event::Base& bevent)->bool {
			const auto e = bevent.cast<event::WindowResizeScreen>();
			this->window.width = e->width;
			this->window.height = e->height;
			return false;
		});
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
				platform::process_events();
			}
		} catch (const std::exception& exc) {
			running = false;
			nova_bark_error("Main Execution Exception: {}", exc.what());
			throw;
		}
	}
}
