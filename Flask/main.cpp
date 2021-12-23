#include "fpch.h"
#include <core/application.h>
#include <event/event.h>

bool t(Nova::Event::Base& e) {
	nova_bark_info("LOL");
	return false;
}

class Game : public Nova::Application {
public:
	Game() : Application("Flask") {
		auto re = Nova::Event::Register(Nova::Event::Type::Keyboard, &t);
		auto e = Nova::Event::Base();
		Nova::Event::fire(e);
	}

	void update() {}
	void render() {}
};

#define NOVA_ENTRY Game
#include <core/entry.h>
