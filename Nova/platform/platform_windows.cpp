#include "npch.h"
#include "meta/head.h"
#if defined(NOVA_WINDOW_NATIVE) && defined(NOVA_OS_WINDOWS)
#include "application.h"

#include "events.h"
#include "input.h"

#include <Windows.h>
#include <windowsx.h>

LRESULT CALLBACK proc_message(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace Nova::platform {

	namespace input {
		constexpr Nova::input::Key key(const unsigned int code) {
			switch (code) {
			case 48:	return Nova::input::Key::N0;
			case 49:	return Nova::input::Key::N1;
			case 50:	return Nova::input::Key::N2;
			case 51:	return Nova::input::Key::N3;
			case 52:	return Nova::input::Key::N4;
			case 53:	return Nova::input::Key::N5;
			case 54:	return Nova::input::Key::N6;
			case 55:	return Nova::input::Key::N7;
			case 56:	return Nova::input::Key::N8;
			case 57:	return Nova::input::Key::N9;
			case 65:	return Nova::input::Key::A;
			case 66:	return Nova::input::Key::B;
			case 67:	return Nova::input::Key::C;
			case 68:	return Nova::input::Key::D;
			case 69:	return Nova::input::Key::E;
			case 70:	return Nova::input::Key::F;
			case 71:	return Nova::input::Key::G;
			case 72:	return Nova::input::Key::H;
			case 73:	return Nova::input::Key::I;
			case 74:	return Nova::input::Key::J;
			case 75:	return Nova::input::Key::K;
			case 76:	return Nova::input::Key::L;
			case 77:	return Nova::input::Key::M;
			case 78:	return Nova::input::Key::N;
			case 79:	return Nova::input::Key::O;
			case 80:	return Nova::input::Key::P;
			case 81:	return Nova::input::Key::Q;
			case 82:	return Nova::input::Key::R;
			case 83:	return Nova::input::Key::S;
			case 84:	return Nova::input::Key::T;
			case 85:	return Nova::input::Key::U;
			case 86:	return Nova::input::Key::V;
			case 87:	return Nova::input::Key::W;
			case 88:	return Nova::input::Key::X;
			case 89:	return Nova::input::Key::Y;
			case 90:	return Nova::input::Key::Z;
			case VK_SHIFT:
			case VK_LSHIFT:	return Nova::input::Key::LSHIFT;
			case VK_CONTROL:
			case VK_LCONTROL:	return Nova::input::Key::LCTRL;
			case VK_MENU:
			case VK_LMENU:	return Nova::input::Key::LALT;
			case VK_LWIN:	return Nova::input::Key::LSUPER;
			case VK_RSHIFT:	return Nova::input::Key::RSHIFT;
			case VK_RCONTROL:	return Nova::input::Key::RCTRL;
			case VK_RMENU:	return Nova::input::Key::RALT;
			case VK_RWIN:	return Nova::input::Key::RSUPER;
			case VK_ESCAPE:	return Nova::input::Key::ESCAPE;
			case VK_RETURN:	return Nova::input::Key::ENTER;
			case VK_TAB:	return Nova::input::Key::TAB;
			case VK_BACK:	return Nova::input::Key::BACKSPACE;
			case VK_SPACE:	return Nova::input::Key::SPACE;
			case VK_OEM_1:	return Nova::input::Key::SEMICOLON;
			case VK_OEM_COMMA:	return Nova::input::Key::COMMA;
			case VK_OEM_PLUS:	return Nova::input::Key::EQUAL;
			case VK_OEM_MINUS:	return Nova::input::Key::MINUS;
			case VK_OEM_2:	return Nova::input::Key::SLASH;
			case VK_OEM_7:	return Nova::input::Key::HASH;
			case VK_OEM_4:	return Nova::input::Key::LBRACKET;
			case VK_OEM_6:	return Nova::input::Key::RBRACKET;
			case VK_OEM_5:	return Nova::input::Key::BACKSLASH;
			case VK_OEM_3:	return Nova::input::Key::APOSTROPHE;
			case VK_OEM_8:	return Nova::input::Key::GRAVE_ACCENT;
			case VK_OEM_PERIOD:	return Nova::input::Key::PERIOD;
			case VK_INSERT:	return Nova::input::Key::INSERT;
			case VK_DELETE:	return Nova::input::Key::DEL;
			case VK_RIGHT:	return Nova::input::Key::RIGHT;
			case VK_LEFT:	return Nova::input::Key::LEFT;
			case VK_DOWN:	return Nova::input::Key::DOWN;
			case VK_UP:	return Nova::input::Key::UP;
			case VK_PRIOR:	return Nova::input::Key::PGUP;
			case VK_NEXT:	return Nova::input::Key::PGDN;
			case VK_HOME:	return Nova::input::Key::HOME;
			case VK_END:	return Nova::input::Key::END;
			case VK_CAPITAL:	return Nova::input::Key::CAPS_LOCK;
			case VK_SCROLL:	return Nova::input::Key::SCROLL_LOCK;
			case VK_NUMLOCK:	return Nova::input::Key::NUM_LOCK;
			case VK_PRINT:	return Nova::input::Key::PRINT_SCREEN;
			case VK_PAUSE:	return Nova::input::Key::PAUSE;
			case VK_NUMPAD0:	return Nova::input::Key::KP_0;
			case VK_NUMPAD1:	return Nova::input::Key::KP_1;
			case VK_NUMPAD2:	return Nova::input::Key::KP_2;
			case VK_NUMPAD3:	return Nova::input::Key::KP_3;
			case VK_NUMPAD4:	return Nova::input::Key::KP_4;
			case VK_NUMPAD5:	return Nova::input::Key::KP_5;
			case VK_NUMPAD6:	return Nova::input::Key::KP_6;
			case VK_NUMPAD7:	return Nova::input::Key::KP_7;
			case VK_NUMPAD8:	return Nova::input::Key::KP_8;
			case VK_NUMPAD9:	return Nova::input::Key::KP_9;
			case VK_ADD:	return Nova::input::Key::KP_ADD;
			case VK_DIVIDE:	return Nova::input::Key::KP_DIVIDE;
			case VK_SUBTRACT:	return Nova::input::Key::KP_SUBTRACT;
			case VK_MULTIPLY:	return Nova::input::Key::KP_MULTIPLY;
			case VK_F1:	return Nova::input::Key::F1;
			case VK_F2:	return Nova::input::Key::F2;
			case VK_F3:	return Nova::input::Key::F3;
			case VK_F4:	return Nova::input::Key::F4;
			case VK_F5:	return Nova::input::Key::F5;
			case VK_F6:	return Nova::input::Key::F6;
			case VK_F7:	return Nova::input::Key::F7;
			case VK_F8:	return Nova::input::Key::F8;
			case VK_F9:	return Nova::input::Key::F9;
			case VK_F10:	return Nova::input::Key::F10;
			case VK_F11:	return Nova::input::Key::F11;
			case VK_F12:	return Nova::input::Key::F12;
			case VK_F13:	return Nova::input::Key::F13;
			case VK_F14:	return Nova::input::Key::F14;
			case VK_F15:	return Nova::input::Key::F15;
			case VK_F16:	return Nova::input::Key::F16;
			case VK_F17:	return Nova::input::Key::F17;
			case VK_F18:	return Nova::input::Key::F18;
			case VK_F19:	return Nova::input::Key::F19;
			case VK_F20:	return Nova::input::Key::F20;
			case VK_F21:	return Nova::input::Key::F21;
			case VK_F22:	return Nova::input::Key::F22;
			case VK_F23:	return Nova::input::Key::F23;
			case VK_F24:	return Nova::input::Key::F24;

			default:
				nova_bark_warn("Unhandled Case [Windows Key Code]: {}", code);
				return Nova::input::Key::NONE;
			}
		}
		constexpr Nova::input::Mouse mouse(const unsigned int code) {
			switch (code) {
			case VK_LBUTTON:	return Nova::input::Mouse::Left;
			case VK_RBUTTON:	return Nova::input::Mouse::Right;
			case VK_MBUTTON:	return Nova::input::Mouse::Middle;
			case VK_XBUTTON1:	return Nova::input::Mouse::VB1;
			case VK_XBUTTON2:	return Nova::input::Mouse::VB2;

			default:
				nova_bark_warn("Unhandled Case [Windows Mouse Button]: {}", code);
				return Nova::input::Mouse::NONE;
			}
		}
	}

	namespace {
		HWND hwnd;
		HINSTANCE instance;
	}

	std::string get_error() {
		const auto code = GetLastError();

		LPSTR message_buffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&message_buffer, 0, NULL);

		std::string message{ message_buffer, size };
		LocalFree(message_buffer);
		return message;
	}

	bool check(const bool check, const std::string_view& message) {
		if (!check) {
			MessageBoxA(hwnd, nova_bark_format("{} : {} {}"sv, message, GetLastError(), get_error()).c_str(), "Error", MB_ICONERROR | MB_OK);
			nova_bark_fatal("{} : {} {}", message, GetLastError(), get_error());
			throw std::runtime_error(message.data());
		}
		return check;
	}

	void Initialize(const std::string_view& name, const core::Window& window) {
		// CONSOLE SETUP
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut && hOut != INVALID_HANDLE_VALUE) {
			DWORD dwMode = 0;
			check(GetConsoleMode(hOut, &dwMode), "Console Handle");

			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			check(SetConsoleMode(hOut, dwMode), "Console Handle");
		}

		nova_bark_init("[Platform] <Windows> ...");

		// WINDOW CREATION
		constexpr auto wnd_cls_name = "nova_window_class"sv;
		instance = GetModuleHandleA(0);

		HICON icon = LoadIcon(instance, IDI_APPLICATION);
		WNDCLASSEXA wc{
			sizeof(WNDCLASSEXA),
			CS_DBLCLKS,
			proc_message,
			0, 0,
			instance,
			icon,
			LoadCursor(NULL, IDC_ARROW),
			NULL, NULL,
			wnd_cls_name.data(),
			NULL
		};

		if (!RegisterClassExA(&wc)) {
			check(GetLastError() == ERROR_CLASS_ALREADY_EXISTS, "Window Registration Failed");
		}

		constexpr auto wstyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME;
		constexpr auto wxstyle = WS_EX_APPWINDOW;

		RECT rect{ 0, 0, 0, 0 };
		AdjustWindowRectEx(&rect, wstyle, false, wxstyle);

		constexpr int x = 100, y = 100;

		hwnd = CreateWindowExA(
			wxstyle, wnd_cls_name.data(), name.data(),
			wstyle, x + rect.left, y + rect.top, window.width() + rect.right - rect.left, window.height() + rect.bottom - rect.top,
			0, 0, instance, 0
		);

		check(hwnd != 0, "Window Creation Failed");

		ShowWindow(hwnd, SW_SHOW);
		nova_bark_init("[Platform] Done!");

	}

	void Termintate() {
		nova_bark_term("[Platform] ...");
		if (hwnd)
			DestroyWindow(hwnd);
		hwnd = nullptr;
		nova_bark_term("[Platform] Done!");
	}

	void process_events() {
		MSG msg;
		while (PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

}

LRESULT CALLBACK proc_message(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
		[[unlikely]] case WM_ERASEBKGND:
			// Notify the OS that erasing will be handled by the application to prevent flicker.
			return 1;
		[[unlikely]] case WM_CLOSE:
			Nova::event::WindowClose().fire();
			return 0;
		[[unlikely]] case WM_DESTROY:
			// Clean Up Tasks
			PostQuitMessage(0);
			return 0;
		[[unlikely]] case WM_SIZE: {
			RECT r;
			GetClientRect(hwnd, &r);
			Nova::event::WindowResizeScreen(r.right - r.left, r.bottom - r.top).fire();
		} break;
		[[likely]] case WM_KEYDOWN:
		[[likely]] case WM_SYSKEYDOWN:
			Nova::platform::event::key_down(Nova::platform::input::key(wparam));
			break;
		[[likely]] case WM_KEYUP:
		[[likely]] case WM_SYSKEYUP:
			Nova::platform::event::key_up(Nova::platform::input::key(wparam));
			break;
		[[likely]] case WM_MOUSEMOVE:
			Nova::platform::event::mouse_move(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			break;
		case WM_MOUSEWHEEL:
			if (const auto y = GET_WHEEL_DELTA_WPARAM(wparam)) [[likely]]
				Nova::platform::event::scroll(y);
			break;
		case WM_LBUTTONDOWN:
			Nova::platform::event::mouse_down(Nova::input::Mouse::Left);	break;
		case WM_MBUTTONDOWN:
			Nova::platform::event::mouse_down(Nova::input::Mouse::Middle);	break;
		case WM_RBUTTONDOWN:
			Nova::platform::event::mouse_down(Nova::input::Mouse::Right);	break;
		case WM_LBUTTONUP:
			Nova::platform::event::mouse_up(Nova::input::Mouse::Left);	break;
		case WM_MBUTTONUP:
			Nova::platform::event::mouse_up(Nova::input::Mouse::Middle);	break;
		case WM_RBUTTONUP:
			Nova::platform::event::mouse_up(Nova::input::Mouse::Right);	break;

		default:
			return DefWindowProcA(hwnd, msg, wparam, lparam);
	}
	return 0;
}

#ifdef NOVA_ABYSS_VULKAN
#include "abyss/nvk/context/context.h"
#include "abyss/nvk/context/surface.h"
#include <vulkan/vulkan_win32.h>
namespace Nova::abyss::nvk::Surface {
	vk::SurfaceKHR create(vk::Instance& instance) {
		nova_bark_init("VK Surface <Windows>");
		VkWin32SurfaceCreateInfoKHR create_info{
			.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
			.hinstance = Nova::platform::instance,
			.hwnd = Nova::platform::hwnd,
		};
		vk::SurfaceKHR surface;
		NVK_RESULT(
			vkCreateWin32SurfaceKHR(instance, &create_info, reinterpret_cast<std::remove_reference_t<decltype(*nova_abyss_api->alloc)>::NativeType*>(nova_abyss_api->alloc), reinterpret_cast<decltype(surface)::CType*>(&surface)),
			"Failed to create vk::SurfaceKHR"
		);
		return surface;
	}
} // namespace Nova::abyss::vkn
#endif	// NOVA_ABYSS_VULKAN

#endif // NOVA_WINDOW_NATIVE && NOVA_OS_WINDOWS
