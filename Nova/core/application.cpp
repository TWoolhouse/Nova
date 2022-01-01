#include "npch.h"
#include "application.h"
#include "platform/application.h"
#include "event/window.h"

#include "abyss/vulkan/context.h"
#include "abyss/vulkan/device.h"

namespace Nova {

	typename decltype(Application::I) Application::I = nullptr;
	typename decltype(Application::clock) Application::clock{};

	Application::Application(const std::string_view& name) : window({ 720, 480 }) {
		nova_assert(!I, "Creating multiple Applications is not allowed!");
		I = this;
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

		abyss::Context aby{ name };
		abyss::Device device(aby);

		nova_bark_init("[Application] Done!");
	}

	Application::~Application() {
		nova_bark_term("[Application] ...");
		platform::Termintate();
		bark::Terminate();
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
