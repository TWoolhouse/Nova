#pragma once
#include "meta/head.h"
#include "core/info.h"
#include "tower.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/context.h"
#endif // NOVA_ABYSS

namespace Nova::abyss {

	class NOVAPI App {
	public:
		inline static App* I = nullptr;

		App(const core::Information& info);
		~App();

	protected:
		bool m_imp;

	public:
		struct FrameDimensions {
			FrameDimensions(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}
			~FrameDimensions() {}

			NODISCARD constexpr inline const auto& width() const noexcept { return m_width; }
			NODISCARD constexpr inline const auto& height() const noexcept { return m_height; }
			NODISCARD constexpr inline const std::pair<const uint32_t&, const uint32_t&> size() const noexcept { return { m_width, m_height }; }

			// Resizes the framebuffer to the requested values.
			// There is not guarantee it will resize to these dimensions.
			// (Probably not a good idea to expose due to the unreliability across OS')
			// void resize(const uint32_t width, const uint32_t height);
		protected:
			friend class App;
			uint32_t m_width, m_height;

		public:
			// Sets the size values, does not perform a resize.
			inline void size(uint32_t width, uint32_t height) noexcept {
				m_width = width; m_height = height;
			}
		} framesize;

	public: // Graphics API Selection
		#if defined(NOVA_ABYSS_VULKAN)
		nvk::Context api;
		#endif // NOVA_ABYSS

		Tower tower;

	protected:
		template<typename ...Ts>
		App(const core::Information& info, Ts... args) :
			m_imp([&](){
				nova_assert(I == nullptr, "Can not create multiple abyss Apps");
				I = this;
				return false;
			}()),
			framesize(info.window.width(), info.window.height()),
			api(info, std::forward<Ts>(args)...),
			tower()
		{}
	};

}

#define nova_abyss_app ::Nova::abyss::App::I
