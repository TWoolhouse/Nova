#pragma once
#include "meta/head.h"

namespace Nova::core {

	struct Window {
	public:
		Window(const uint32_t width, const uint32_t height) : m_width(width), m_height(height) {}
		~Window() {}

		NODISCARD constexpr inline const auto& width() const noexcept { return m_width; }
		NODISCARD constexpr inline const auto& height() const noexcept { return m_height; }
		NODISCARD constexpr inline const std::pair<const uint32_t&, const uint32_t&> size() const noexcept { return { m_width, m_height }; }

		// Resizes the window to the requested values.
		void resize(const uint32_t width, const uint32_t height);
	protected:
		uint32_t m_width, m_height;

		friend class Application;
		// Sets the size values, does not perform a resize.
		inline void size(const uint32_t width, const uint32_t height) noexcept {
			m_width = width; m_height = height;
		}
	};

}
