#include "npch.h"
#ifdef NOVA_OS_WINDOWS
#include "platform.h"

#include <Windows.h>

struct State {
	HINSTANCE instance;
	HWND hwnd;
} static *state;

namespace Nova {

	LRESULT CALLBACK proc_message(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void platform::Initialize(const std::string_view& name, const unsigned int width, const unsigned int height) {
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

	void platform::Termintate() {
		if (state->hwnd)
			DestroyWindow(state->hwnd);
		delete state;
	}

	void platform::pump_messages() {
		MSG msg;
		while (PeekMessageA(&msg, state->hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	LRESULT CALLBACK proc_message(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		return DefWindowProcA(hwnd, msg, wparam, lparam);
	}

}

#endif // NOVA_OS_WINDOWS
