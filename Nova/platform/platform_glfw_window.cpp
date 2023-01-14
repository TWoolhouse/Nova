#include "npch.h"
#include "meta/head.h"
#ifdef NOVA_WINDOW_GLFW
#include "application.h"
#include "input.h"
#include "events.h"

#include "abyss/opengl/opengl.h"
#include <GLFW/glfw3.h>

void GLAPIENTRY callback_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	constexpr auto header = "[GL]: {} -> {}"sv;
	switch (severity) {
		case GL_DEBUG_TYPE_ERROR:
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return nova_bark_error(header, type, message);
		case GL_DEBUG_TYPE_PORTABILITY:
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return nova_bark_warn(header, type, message);
		case GL_DEBUG_TYPE_MARKER: return nova_bark_debug(header, type, message);
		case GL_DEBUG_TYPE_PERFORMANCE: return nova_bark_trace(header, type, message);
		default:
			return nova_bark_info(header, type, message);
	}
}

namespace Nova::platform {

	namespace input {
		constexpr Nova::input::Key key(const unsigned int code) {
			switch (code) {
			case GLFW_KEY_0:	return Nova::input::Key::N0;
			case GLFW_KEY_1:	return Nova::input::Key::N1;
			case GLFW_KEY_2:	return Nova::input::Key::N2;
			case GLFW_KEY_3:	return Nova::input::Key::N3;
			case GLFW_KEY_4:	return Nova::input::Key::N4;
			case GLFW_KEY_5:	return Nova::input::Key::N5;
			case GLFW_KEY_6:	return Nova::input::Key::N6;
			case GLFW_KEY_7:	return Nova::input::Key::N7;
			case GLFW_KEY_8:	return Nova::input::Key::N8;
			case GLFW_KEY_9:	return Nova::input::Key::N9;
			case GLFW_KEY_A:	return Nova::input::Key::A;
			case GLFW_KEY_B:	return Nova::input::Key::B;
			case GLFW_KEY_C:	return Nova::input::Key::C;
			case GLFW_KEY_D:	return Nova::input::Key::D;
			case GLFW_KEY_E:	return Nova::input::Key::E;
			case GLFW_KEY_F:	return Nova::input::Key::F;
			case GLFW_KEY_G:	return Nova::input::Key::G;
			case GLFW_KEY_H:	return Nova::input::Key::H;
			case GLFW_KEY_I:	return Nova::input::Key::I;
			case GLFW_KEY_J:	return Nova::input::Key::J;
			case GLFW_KEY_K:	return Nova::input::Key::K;
			case GLFW_KEY_L:	return Nova::input::Key::L;
			case GLFW_KEY_M:	return Nova::input::Key::M;
			case GLFW_KEY_N:	return Nova::input::Key::N;
			case GLFW_KEY_O:	return Nova::input::Key::O;
			case GLFW_KEY_P:	return Nova::input::Key::P;
			case GLFW_KEY_Q:	return Nova::input::Key::Q;
			case GLFW_KEY_R:	return Nova::input::Key::R;
			case GLFW_KEY_S:	return Nova::input::Key::S;
			case GLFW_KEY_T:	return Nova::input::Key::T;
			case GLFW_KEY_U:	return Nova::input::Key::U;
			case GLFW_KEY_V:	return Nova::input::Key::V;
			case GLFW_KEY_W:	return Nova::input::Key::W;
			case GLFW_KEY_X:	return Nova::input::Key::X;
			case GLFW_KEY_Y:	return Nova::input::Key::Y;
			case GLFW_KEY_Z:	return Nova::input::Key::Z;
			case GLFW_KEY_LEFT_SHIFT:	return Nova::input::Key::LSHIFT;
			case GLFW_KEY_LEFT_CONTROL:	return Nova::input::Key::LCTRL;
			case GLFW_KEY_MENU:
			case GLFW_KEY_LEFT_ALT:	return Nova::input::Key::LALT;
			case GLFW_KEY_LEFT_SUPER:	return Nova::input::Key::LSUPER;
			case GLFW_KEY_RIGHT_SHIFT:	return Nova::input::Key::RSHIFT;
			case GLFW_KEY_RIGHT_CONTROL:	return Nova::input::Key::RCTRL;
			case GLFW_KEY_RIGHT_ALT:	return Nova::input::Key::RALT;
			case GLFW_KEY_RIGHT_SUPER:	return Nova::input::Key::RSUPER;
			case GLFW_KEY_ESCAPE:	return Nova::input::Key::ESCAPE;
			case GLFW_KEY_ENTER:	return Nova::input::Key::ENTER;
			case GLFW_KEY_TAB:	return Nova::input::Key::TAB;
			case GLFW_KEY_BACKSPACE:	return Nova::input::Key::BACKSPACE;
			case GLFW_KEY_SPACE:	return Nova::input::Key::SPACE;
			case GLFW_KEY_SEMICOLON:	return Nova::input::Key::SEMICOLON;
			case GLFW_KEY_COMMA:	return Nova::input::Key::COMMA;
			case GLFW_KEY_EQUAL:	return Nova::input::Key::EQUAL;
			case GLFW_KEY_MINUS:	return Nova::input::Key::MINUS;
			case GLFW_KEY_SLASH:	return Nova::input::Key::SLASH;
			case GLFW_KEY_LEFT_BRACKET:	return Nova::input::Key::LBRACKET;
			case GLFW_KEY_RIGHT_BRACKET:	return Nova::input::Key::RBRACKET;
			case GLFW_KEY_BACKSLASH:	return Nova::input::Key::BACKSLASH;
			case GLFW_KEY_APOSTROPHE:	return Nova::input::Key::APOSTROPHE;
			case GLFW_KEY_GRAVE_ACCENT:	return Nova::input::Key::GRAVE_ACCENT;
			case GLFW_KEY_PERIOD:	return Nova::input::Key::PERIOD;
			case GLFW_KEY_INSERT:	return Nova::input::Key::INSERT;
			case GLFW_KEY_DELETE:	return Nova::input::Key::DEL;
			case GLFW_KEY_RIGHT:	return Nova::input::Key::RIGHT;
			case GLFW_KEY_LEFT:	return Nova::input::Key::LEFT;
			case GLFW_KEY_DOWN:	return Nova::input::Key::DOWN;
			case GLFW_KEY_UP:	return Nova::input::Key::UP;
			case GLFW_KEY_PAGE_UP:	return Nova::input::Key::PGUP;
			case GLFW_KEY_PAGE_DOWN:	return Nova::input::Key::PGDN;
			case GLFW_KEY_HOME:	return Nova::input::Key::HOME;
			case GLFW_KEY_END:	return Nova::input::Key::END;
			case GLFW_KEY_CAPS_LOCK:	return Nova::input::Key::CAPS_LOCK;
			case GLFW_KEY_SCROLL_LOCK:	return Nova::input::Key::SCROLL_LOCK;
			case GLFW_KEY_NUM_LOCK:	return Nova::input::Key::NUM_LOCK;
			case GLFW_KEY_PRINT_SCREEN:	return Nova::input::Key::PRINT_SCREEN;
			case GLFW_KEY_PAUSE:	return Nova::input::Key::PAUSE;
			case GLFW_KEY_KP_0:	return Nova::input::Key::KP_0;
			case GLFW_KEY_KP_1:	return Nova::input::Key::KP_1;
			case GLFW_KEY_KP_2:	return Nova::input::Key::KP_2;
			case GLFW_KEY_KP_3:	return Nova::input::Key::KP_3;
			case GLFW_KEY_KP_4:	return Nova::input::Key::KP_4;
			case GLFW_KEY_KP_5:	return Nova::input::Key::KP_5;
			case GLFW_KEY_KP_6:	return Nova::input::Key::KP_6;
			case GLFW_KEY_KP_7:	return Nova::input::Key::KP_7;
			case GLFW_KEY_KP_8:	return Nova::input::Key::KP_8;
			case GLFW_KEY_KP_9:	return Nova::input::Key::KP_9;
			case GLFW_KEY_KP_ADD:	return Nova::input::Key::KP_ADD;
			case GLFW_KEY_KP_DIVIDE:	return Nova::input::Key::KP_DIVIDE;
			case GLFW_KEY_KP_SUBTRACT:	return Nova::input::Key::KP_SUBTRACT;
			case GLFW_KEY_KP_MULTIPLY:	return Nova::input::Key::KP_MULTIPLY;
			case GLFW_KEY_F1:	return Nova::input::Key::F1;
			case GLFW_KEY_F2:	return Nova::input::Key::F2;
			case GLFW_KEY_F3:	return Nova::input::Key::F3;
			case GLFW_KEY_F4:	return Nova::input::Key::F4;
			case GLFW_KEY_F5:	return Nova::input::Key::F5;
			case GLFW_KEY_F6:	return Nova::input::Key::F6;
			case GLFW_KEY_F7:	return Nova::input::Key::F7;
			case GLFW_KEY_F8:	return Nova::input::Key::F8;
			case GLFW_KEY_F9:	return Nova::input::Key::F9;
			case GLFW_KEY_F10:	return Nova::input::Key::F10;
			case GLFW_KEY_F11:	return Nova::input::Key::F11;
			case GLFW_KEY_F12:	return Nova::input::Key::F12;
			case GLFW_KEY_F13:	return Nova::input::Key::F13;
			case GLFW_KEY_F14:	return Nova::input::Key::F14;
			case GLFW_KEY_F15:	return Nova::input::Key::F15;
			case GLFW_KEY_F16:	return Nova::input::Key::F16;
			case GLFW_KEY_F17:	return Nova::input::Key::F17;
			case GLFW_KEY_F18:	return Nova::input::Key::F18;
			case GLFW_KEY_F19:	return Nova::input::Key::F19;
			case GLFW_KEY_F20:	return Nova::input::Key::F20;
			case GLFW_KEY_F21:	return Nova::input::Key::F21;
			case GLFW_KEY_F22:	return Nova::input::Key::F22;
			case GLFW_KEY_F23:	return Nova::input::Key::F23;
			case GLFW_KEY_F24:	return Nova::input::Key::F24;

			default:
				return Nova::input::Key::NONE;
			}
		}
		constexpr Nova::input::Mouse mouse(const unsigned int code) {
			switch (code) {
			case GLFW_MOUSE_BUTTON_LEFT:	return Nova::input::Mouse::Left;
			case GLFW_MOUSE_BUTTON_RIGHT:	return Nova::input::Mouse::Right;
			case GLFW_MOUSE_BUTTON_MIDDLE:	return Nova::input::Mouse::Middle;
			case GLFW_MOUSE_BUTTON_4:	return Nova::input::Mouse::VB1;
			case GLFW_MOUSE_BUTTON_5:	return Nova::input::Mouse::VB2;

			default:
				return Nova::input::Mouse::NONE;
			}
		}
	}

	namespace {
		GLFWwindow* window;
	}

	void register_callbacks();

	void Initialize(const std::string_view& name, const core::Window& window_state) {
		nova_bark_init("[Platform] <GLFW> ...");
		if (!glfwInit())	nova_bark_fatal("GLFW Failed to Initialise!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(window_state.width(), window_state.height(), name.data(), NULL, NULL);
		if (!window) {
			glfwTerminate();
			nova_bark_fatal("GLFW Failed to create Window");
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) nova_bark_fatal("GLAD Failed to initialize");

		#ifndef NOVA_DEBUG
		glDisable(GL_DEBUG_OUTPUT);
		#else
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(callback_error, 0);
		#endif // !NOVA_DEBUG

		register_callbacks();
		nova_bark_init("[Platform] Done!");
	}

	void Termintate() {
		nova_bark_term("[Platform] ...");
		if (window) {
			glfwTerminate();
		}
		window = nullptr;
		nova_bark_term("[Platform] Done!");
	}

	void process_events() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void register_callbacks() {
		glfwSetWindowCloseCallback(window, [](GLFWwindow*) {
			Nova::event::WindowClose().fire();
		});
		glfwSetWindowSizeCallback(window, [](GLFWwindow*, int width, int height) {
			Nova::event::WindowResizeScreen(width, height).fire();
		});
		glfwSetKeyCallback(window, [](GLFWwindow*, int key, int scancode, int action, int mods) {
			switch (action) {
			case GLFW_PRESS:
			case GLFW_REPEAT:	return Nova::platform::event::key_down(Nova::platform::input::key(key));
			case GLFW_RELEASE:	return Nova::platform::event::key_up(Nova::platform::input::key(key));
			}
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow*, double x, double y) {
			Nova::platform::event::mouse_move(x, y);
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow*, int button, int action, int mods) {
			switch (action) {
			case GLFW_PRESS:	return Nova::platform::event::mouse_down(Nova::platform::input::mouse(button));
			case GLFW_RELEASE:	return Nova::platform::event::mouse_up(Nova::platform::input::mouse(button));
			}
		});
		glfwSetScrollCallback(window, [](GLFWwindow*, double x, double y) {
			if (y) [[likely]]
				Nova::platform::event::scroll(y);
		});
		glfwSetWindowFocusCallback(window, [](GLFWwindow*, int gain) {
			gain ? Nova::event::WindowFocusGain().fire() : Nova::event::WindowFocusLost().fire();
		});
		glfwSetWindowPosCallback(window, [](GLFWwindow*, int x, int y) {
			Nova::event::WindowMove(x, y).fire();
		});

	}

}

#endif // NOVA_PLATFORM_GLFW
