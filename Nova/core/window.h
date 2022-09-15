#pragma once
#include "meta/head.h"

namespace Nova::core {

	struct Window {
	public:
		Window(const unsigned int width, const unsigned int height) : m_width(width), m_height(height) {}
		~Window() {}

		NODISCARD constexpr inline const auto& width() const noexcept { return m_width; }
		NODISCARD constexpr inline const auto& height() const noexcept { return m_height; }
		NODISCARD constexpr inline const std::pair<const unsigned int&, const unsigned int&> size() const noexcept { return { m_width, m_height }; }


		// Resizes the window to the requested values.
		void resize(const unsigned int width, const unsigned int height);
	protected:
		unsigned int m_width, m_height;

		friend class Application;
		// Sets the size values, does not perform a resize.
		inline void size(const unsigned int width, const unsigned int height) noexcept {
			m_width = width; m_height = height;
		}
	};

}
