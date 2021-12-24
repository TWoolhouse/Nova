#include "fpch.h"

bool simple_quit(Nova::event::Base& event) {
	if (auto e = event.cast<Nova::event::KeyPress>()) {
		nova_bark_info("Key: {}", e->key);
		if (e->key == Nova::input::Key::ESCAPE)
			return Nova::event::WindowClose().fire();
	}
	return false;
}

class Game : public Nova::Application {
public:
	Game() : Application("Flask") {
		nova_bark_debug("Creating Flask");
		Nova::event::Register(Nova::event::Type::KeyPress, &simple_quit);
	}

	void update() {}
	void render() {}
};

#define NOVA_ENTRY Game
#include <nova_entry.h>
