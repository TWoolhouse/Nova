#include "fpch.h"

// TESTING
#include "abyss/shader.h"
#include "abyss/shader_graphics.h"

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
	unsigned int frame_count_temp = 0;
	Nova::event::Ticket events;
	Game() :
		Application("Flask"),
		events(Nova::event::dispatcher.subscribe(Nova::event::Type::KeyPress, &simple_quit)),

		// Temporary Graphics Stuff
		pipeline(nova_abyss_app->tower.renderpass, {
			{ Nova::abyss::Shader::Stage::Vertex, "start/first/.vert" },
			{ Nova::abyss::Shader::Stage::Fragment, "start/first/.frag" },
		})

	{}

	void update() {}

	// Temporary Graphics Stuff
	Nova::abyss::shader::Graphics pipeline;

	void render(Nova::abyss::Flight& flight) {
		static constexpr bool max_frames = false;
		static constexpr auto req = 1.f / 60;
		if (clock > req)
			nova_bark_debug("FPS: {:.1f}\tFrame Time: {:>5.1f}ms", 1 / clock, clock * 1000);
		if ((frame_count_temp++) > 10 && max_frames) {
			nova_bark_debug("Max Frametime: {}", frame_count_temp);
			Nova::event::WindowClose().fire();
		}

		flight.commands.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
		flight.commands.draw(3, 1, 0, 0);
	}
};

#define NOVA_ENTRY Game
#include <nova_entry.h>
