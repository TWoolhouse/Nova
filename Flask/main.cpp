#include "fpch.h"

bool simple_quit(Nova::event::Handle& event) {
	if (auto e = event.cast<Nova::event::KeyPress>()) {
		nova_bark_trace("Key: {} {}", e->key, static_cast<char>(e->key));
		if (e->key == Nova::input::Key::ESCAPE || ((e->key == Nova::input::Key::F4) && Nova::input::poll(Nova::input::Key::LALT)))
			return Nova::event::WindowClose().fire();
	}
	return false;
}

class Game : public Nova::core::Application {
public:
	Game() : Application("Flask") {
		Nova::event::dispatcher.subscribe(Nova::event::Type::KeyPress, &simple_quit);
	}

	void update() {}
	void render() {
		static constexpr auto req = 1.f / 240.f;
		if (clock > req)
		nova_bark_debug("FPS: {} Frame Time: {}", 1 / clock, clock);
	}
};

#define NOVA_ENTRY Game
#include <nova_entry.h>
