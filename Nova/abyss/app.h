#pragma once
#include "meta/head.h"
#include "tower.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/context.h"
#endif // NOVA_ABYSS

namespace Nova::abyss {

	class NOVAPI App {
	public:
		inline static App* I = nullptr;

		App();
		~App();

	protected:
		bool m_imp;

	public:
		struct FrameDimensions {
			FrameDimensions() : m_width(0), m_height(0) {}
			~FrameDimensions() {}

			constexpr inline NODISCARD const auto& width() const noexcept { return m_width; }
			constexpr inline NODISCARD const auto& height() const noexcept { return m_height; }
			constexpr inline NODISCARD const std::pair<const unsigned int&, const unsigned int&> size() const noexcept { return { m_width, m_height }; }

			// Resizes the framebuffer to the requested values.
			// There is not guarantee it will resize to these dimensions.
			// (Probably not a good idea to expose due to the unreliability across OS')
			// void resize(const unsigned int width, const unsigned int height);
		protected:
			friend class App;
			unsigned int m_width, m_height;

		public:
			// Sets the size values, does not perform a resize.
			inline void size(const unsigned int width, const unsigned int height) noexcept {
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
		App(Ts... args) :
			m_imp([&](){
				nova_assert(I == nullptr, "Can not create multiple abyss Apps");
				I = this;
				return false;
			}()),
			framesize(),
			api(std::forward<Ts>(args)...),
			tower()
		{}
	};

}

#define nova_abyss_app ::Nova::abyss::App::I
