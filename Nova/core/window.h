#pragma once
#include "meta/head.h"

namespace Nova::core {

	struct Window {
	public:
		Window(const unsigned int width, const unsigned int height) : m_width(width), m_height(height) {}
		~Window() {}

		constexpr inline NODISCARD const auto& width() const noexcept { return m_width; }
		constexpr inline NODISCARD const auto& height() const noexcept { return m_height; }

		// Sets the size values, does not perform a resize.
		inline void size(const unsigned int width, const unsigned int height) noexcept {
			m_width = width; m_height = height;
		}

		// Resizes the window to the requested values.
		void resize(const unsigned int width, const unsigned int height);
	protected:
		unsigned int m_width, m_height;
	};

}