#pragma once
#include "npch.h"
#include "entry.h"
#include <vendor/gtest/gtest.h>

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
		static Application* Create();
		Application(const std::string_view& name);
		virtual ~Application();

	protected:
		friend int ::NOVA_MAIN(int argc, char const* argv[]);
		void execute() {}
	};
}
