#include "npch.h"
#include "bark/bark.h"
#include "application.h"
#include "platform/application.h"
#include "event/window.h"
#include "abyss/abyss.h"

namespace Nova::core {

	typename decltype(Application::I) Application::I = nullptr;
	typename decltype(Application::clock) Application::clock{};

	Application::Application(const std::string_view& name) : window({ 720, 480 }) {
		nova_assert(!I, "Creating multiple Applications is not allowed!");
		I = this;

		nova_bark_timer("Startup");
		clock.update();
		bark::Initialize();
		platform::Initialize(name, window.width, window.height);

		// Events
		event::dispatcher.subscribe(event::Type::WindowClose, [this](event::Handle&)->bool { this->terminate(); return false; });
		event::dispatcher.subscribe(event::Type::WindowResizeScreen, [this](event::Handle& event)->bool {
			const auto e = event.cast<event::WindowResizeScreen>();
			this->window.width = e->width;
			this->window.height = e->height;
			return false;
		});

		abyss::Initialize(name);

		clock.update();
		nova_bark_init("[Application] Done!");
	}

	Application::~Application() {
		nova_bark_term("[Application] ...");
		abyss::Terminate();
		platform::Termintate();
		event::dispatcher.clear();
		bark::Terminate();

		I = nullptr;
	}

	void Application::execute() {
		running = true;
		try {
			while (running) {
				clock.update();
				render();
				platform::process_events();
				std::this_thread::yield();
			}
		} catch (const std::exception& exc) {
			running = false;
			nova_bark_error("Main Execution Exception: {}", exc.what());
			throw;
		}
	}
}
