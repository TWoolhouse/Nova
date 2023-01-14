#pragma once
#include "meta/head.h"
#include "vk.h"

// Bindings
#include "shader/graphics.h"
#include "buffer/vertex.h"

namespace Nova::abyss::nvk {
	class CommandQueue : public OPVK<CommandQueue, vk::CommandBuffer> {
	public:
		vk::CommandBuffer self;

		// Bindings

		void bind(shader::Graphics& pipeline) {
			self.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
		}

		template<typename V>
		void bind(uint32_t binding, buffer::Vertex<V>& buffer) {
			self.bindVertexBuffers(binding, { buffer.buffer }, { 0 });
		}

		template<typename V>
		void draw(buffer::Vertex<V>& buffer) {
			//self.draw(buffer.buffer)
		}

	};
}