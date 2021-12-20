#include "fpch.h"
#include <test.h>
#include <core/application.h>
#define NOVA_ENTRY
#include <core/entry.h>

Nova::Application* Nova::Application::Create() {
	return new Nova::Application("Flask");
}
