#include "npch.h"
#ifdef NOVA_OS_WINDOWS
#include "platform.h"
#include "platform_events.h"

#include <Windows.h>
#include <windowsx.h>

struct State {
	HINSTANCE instance;
	HWND hwnd;
} static* state;

LRESULT CALLBACK proc_message(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

void Nova::platform::Initialize(const std::string_view& name, const unsigned int width, const unsigned int height) {
	constexpr auto wnd_cls_name = "nova_window_class"sv;
	state = new State{ GetModuleHandleA(0), 0 };

	HICON icon = LoadIcon(state->instance, IDI_APPLICATION);
	WNDCLASSEXA wc{
		sizeof(WNDCLASSEXA),
		CS_DBLCLKS,
		proc_message,
		0, 0,
		state->instance,
		icon,
		LoadCursor(NULL, IDC_ARROW),
		NULL, NULL,
		wnd_cls_name.data(),
		NULL
	};

	if (!RegisterClassExA(&wc)) {
		constexpr auto msg = "Window Registration Failed"sv;
		nova_bark_fatal("{} Error:{}", msg, GetLastError());
		MessageBoxA(state->hwnd, msg.data(), "Error", MB_ICONERROR | MB_OK);
		return;
	}

	constexpr auto wstyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME;
	constexpr auto wxstyle = WS_EX_APPWINDOW;

	RECT rect{ 0, 0, 0, 0 };
	AdjustWindowRectEx(&rect, wstyle, false, wxstyle);

	constexpr int x = 100, y = 100;

	state->hwnd = CreateWindowExA(
		wxstyle, wnd_cls_name.data(), name.data(),
		wstyle, x + rect.left, y + rect.top, width + rect.right - rect.left, height + rect.bottom - rect.top,
		0, 0, state->instance, 0
	);

	if (state->hwnd == 0) {
		constexpr auto msg = "Window Creation Failed"sv;
		nova_bark_fatal("{} Error:{}", msg, GetLastError());
		MessageBoxA(state->hwnd, msg.data(), "Error", MB_ICONERROR | MB_OK);
		return;
	}

	ShowWindow(state->hwnd, SW_SHOW);

}

void Nova::platform::Termintate() {
	if (state->hwnd)
		DestroyWindow(state->hwnd);
	delete state;
}

void Nova::platform::pump_messages() {
	MSG msg;
	while (PeekMessageA(&msg, state->hwnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

LRESULT CALLBACK proc_message(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_ERASEBKGND:
		// Notify the OS that erasing will be handled by the application to prevent flicker.
		return 1;
	case WM_CLOSE:
		Nova::event::WindowClose().fire();
		return 0;
	case WM_DESTROY:
		// Clean Up Tasks
		PostQuitMessage(0);
		return 0;
	case WM_SIZE: {
			// Get the updated size.
			// RECT r;
			// GetClientRect(hwnd, &r);
			// u32 width = r.right - r.left;
			// u32 height = r.bottom - r.top;

			// TODO: Fire an event for window resize.
		} break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		Nova::pevent::key_down(Nova::input::Key(wparam));
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Nova::pevent::key_up(Nova::input::Key(wparam));
		break;
	case WM_MOUSEMOVE:
		Nova::pevent::mouse_move(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	case WM_MOUSEWHEEL:
		if (const auto z = GET_WHEEL_DELTA_WPARAM(wparam))
			Nova::event::MouseScroll((z < 0) ? -1 : 1);
		break;
	case WM_LBUTTONDOWN:
		Nova::pevent::mouse_down(Nova::input::Mouse::Left);	break;
	case WM_MBUTTONDOWN:
		Nova::pevent::mouse_down(Nova::input::Mouse::Middle);	break;
	case WM_RBUTTONDOWN:
		Nova::pevent::mouse_down(Nova::input::Mouse::Right);	break;
	case WM_LBUTTONUP:
		Nova::pevent::mouse_up(Nova::input::Mouse::Left);	break;
	case WM_MBUTTONUP:
		Nova::pevent::mouse_up(Nova::input::Mouse::Middle);	break;
	case WM_RBUTTONUP:
		Nova::pevent::mouse_up(Nova::input::Mouse::Right);	break;

	default:
		return DefWindowProcA(hwnd, msg, wparam, lparam);
	}
	return 0;
}

#endif // NOVA_OS_WINDOWS
