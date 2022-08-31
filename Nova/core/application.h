#pragma once
#include "meta/head.h"
#include "blip/blip.h"
#include "window.h"
#include "abyss/flight.h"

#ifdef NOVA_DEBUG
#define NOVA_MAIN main
#else
#ifdef NOVA_OS_WINDOWS
#define NOVA_MAIN WinMain
#else
#define NOVA_MAIN main
#endif
#endif
int NOVA_MAIN(int argc, char const* argv[]);

namespace Nova::core {
	class NOVAPI Application {
	public:
		Application(const std::string_view& name);
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
		virtual ~Application();

		virtual void update() = 0;
		virtual void render(abyss::Flight&) = 0;

		inline void terminate() { running = false;};

	private:
		friend int ::NOVA_MAIN(int argc, char const* argv[]);
		void execute();

	protected:
		bool running = false;
	public:
		// Application Instance
		inline static Application* I = nullptr;
		inline static blip::Clock clock;
		Window window;
	};

}

#define nova_app ::Nova::core::Application::I
