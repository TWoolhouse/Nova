#include "npch.h"
#include "bark/bark.h"
#include "application.h"
#include "platform/application.h"
#include "event/window.h"
#include "abyss/abyss.h"

void t();

namespace Nova::core {

	typename decltype(Application::I) Application::I = nullptr;
	typename decltype(Application::clock) Application::clock{};

	Application::Application(const std::string_view& name) : window(720, 480) {
		nova_assert(!I, "Creating multiple Applications is not allowed!");
		I = this;

		nova_bark_timer("Startup");
		clock.update();
		bark::Initialize();
		platform::Initialize(name, window);

		// Events
		event::dispatcher.subscribe({
			{ event::Type::WindowClose, [&](event::Handle&)->bool { this->terminate(); return false; } },
			{ event::Type::WindowResizeScreen, [&](event::Handle& event)->bool {
					const auto e = event.cast<event::WindowResizeScreen>();
					this->window.size(e->width, e->height);
					return false;
				}
			}, }
		).orphan();

		abyss::Initialize(name);

		clock.update();
		nova_bark_init("[Application] Done!");
		t();
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
				platform::process_events();

				abyss::acquire();
				render();
				abyss::release();

				std::this_thread::yield();
			}
		} catch (const std::exception& exc) {
			running = false;
			nova_bark_error("Main Execution Exception: {}", exc.what());
			throw;
		}
	}
}
