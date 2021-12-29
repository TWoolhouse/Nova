#include "npch.h"
#include "application.h"
#include "platform/platform.h"
#include "event/window.h"

namespace Nova {

	typename decltype(Application::I) Application::I = nullptr;
	typename decltype(Application::clock) Application::clock{};

	Application::Application(const std::string_view& name) : window({ 720, 480 }) {
		I = this;
		Bark::Initialize();
		platform::Initialize(name, window.width, window.height);

		// Events
		event::dispatcher.subscribe(event::Type::WindowClose, [this](event::Handle&)->bool { this->terminate(); return false; });
		event::dispatcher.subscribe(event::Type::WindowResizeScreen, [this](event::Handle& event)->bool {
			const auto e = event.cast<event::WindowResizeScreen>();
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
				clock.update();
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
