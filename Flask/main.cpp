#include "fpch.h"

// TESTING
#include "abyss/shader.h"
#include "abyss/shader_graphics.h"
#include "abyss/buffer_vertex.h"

bool simple_quit(Nova::event::Handle& event) {
	if (auto e = event.cast<Nova::event::KeyPress>()) {
		nova_bark_trace("Key: {} {}", e->key, static_cast<char>(e->key));
		if (e->key == Nova::input::Key::ESCAPE || ((e->key == Nova::input::Key::F4) && Nova::input::poll(Nova::input::Key::LALT)))
			return Nova::event::WindowClose().fire();
	}
	return false;
}

struct Vertex {
	using Spec = Nova::meta::pack<Nova::mlb::vec3, Nova::mlb::vec3>;
	Nova::mlb::vec3 position;
	Nova::mlb::vec3 colour;
};
std::vector<Vertex> verticies{
	{ { 0.1, -0.6, 0.0}, {0.0, 0.0, 0.0} },
	{ { 0.6,  0.6, 1.0}, {0.0, 0.0, 0.0} },
	{ {-0.6,  0.6, 0.0}, {0.0, 0.0, 1.0} },

	{ { 0.0, -0.5, 0.0}, {1.0, 0.0, 0.0} },
	{ { 0.5,  0.5, 0.0}, {0.0, 1.0, 0.0} },
	{ {-0.5,  0.5, 0.0}, {0.0, 0.0, 1.0} },
};

struct UBOData {
	Nova::mlb::vec4 colour;
};

class Game : public Nova::core::Application {
public:
	unsigned int frame_count_temp = 0;
	Nova::event::Ticket events;
	Game() :
		Application("Flask"),
		events(Nova::event::dispatcher.subscribe(Nova::event::Type::KeyPress, &simple_quit)),

		// Temporary Graphics Stuff
		pipeline(nova_abyss_app->tower.renderpass, {
			{ Nova::abyss::Shader::Stage::Vertex, "start/simple/.vert" },
			{ Nova::abyss::Shader::Stage::Fragment, "start/simple/.frag" },
		}, Nova::meta::pack<Nova::abyss::buffer::Vertex<Vertex>>{}),
		buffer_vertex(verticies.size())
	{
		void* data = buffer_vertex.buffer.map();
		memcpy(data, verticies.data(), verticies.size() * sizeof(Vertex));
	}

	void update() {
		auto& vertex = reinterpret_cast<Vertex*>( buffer_vertex.buffer.map())[4];
		vertex.colour.g = (Nova::mlb::sin(nova_app->clock.elapsed().count()) + 1.0f) / 2.0f;
	}

	// Temporary Graphics Stuff
	Nova::abyss::shader::Graphics pipeline;
	Nova::abyss::buffer::Vertex<Vertex> buffer_vertex;

	void render(Nova::abyss::Flight& flight) {
		static constexpr size_t max_frames = 0;
		static constexpr auto req = 1.f / 30;
		if (clock > req)
			nova_bark_debug("FPS: {:.1f}\tFrame Time: {:>5.1f}ms", 1 / clock, clock * 1000);
		if ((frame_count_temp++) > max_frames && max_frames) {
			nova_bark_debug("Max Frametime: {}", frame_count_temp);
			Nova::event::WindowClose().fire();
		}

		update();

		flight.commands.bind(pipeline);
		flight.commands.bind(0, buffer_vertex);
		flight.commands.self.draw(verticies.size(), 1, 0, 0);

	}

};

#define NOVA_ENTRY Game
#include <nova_entry.h>
