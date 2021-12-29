#pragma once
#include "npch.h"
#include "deltatime.h"

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

namespace Nova {
	class NOVAPI Application {
	public:
		Application(const std::string_view& name);
		virtual ~Application();

		virtual void update() = 0;
		virtual void render() = 0;

		inline void terminate() { running = false;};

	private:
		friend int ::NOVA_MAIN(int argc, char const* argv[]);
		void execute();

	protected:
		bool running = false;
		struct Window {
			unsigned int width, height;
		};
	public:
		// Application Instance
		static Application* I;
		static Clock clock;
		Window window;
	};
}
