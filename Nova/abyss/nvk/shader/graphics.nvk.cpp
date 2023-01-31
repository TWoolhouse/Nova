#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "graphics.h"
#include "../context.h"

namespace Nova::abyss::nvk::shader {

	Graphics::Graphics(const abyss::Renderpass& renderpass, const std::initializer_list<abyss::ShaderCode>& stages, vk::VertexInputBindingDescription binding, std::span<vk::VertexInputAttributeDescription> attributes) {

		vk::PipelineVertexInputStateCreateInfo info_input_vertex{
			.vertexBindingDescriptionCount = 1,
			.pVertexBindingDescriptions = &binding,
			.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributes.size()),
			.pVertexAttributeDescriptions = attributes.data(),
		};

		// TODO: Expose primative type.
		vk::PipelineInputAssemblyStateCreateInfo info_input_assembly{
			.topology = vk::PrimitiveTopology::eTriangleList,
			.primitiveRestartEnable = VK_FALSE,
		};

		// TODO: Dynamic viewport
		vk::Viewport viewport{
			.x = 0.0f,
			.y = 0.0f,
			.width = static_cast<float>(nova_abyss_app->framesize.width()),
			.height = static_cast<float>(nova_abyss_app->framesize.height()),
			.minDepth = 0.0f,
			.maxDepth = 1.0f,
		};
		vk::Rect2D scissor{
			.offset = { 0, 0 },
			.extent = vk::Extent2D{
				nova_abyss_app->framesize.width(),
				nova_abyss_app->framesize.height(),
			},
		};

		vk::PipelineViewportStateCreateInfo info_viewport{
			.viewportCount = 1,
			.pViewports = &viewport,
			.scissorCount = 1,
			.pScissors = &scissor,
		};

		// TODO: Expose rasterisation options
		vk::PipelineRasterizationStateCreateInfo info_rasterizer{
			.depthClampEnable = VK_FALSE,
			.rasterizerDiscardEnable = VK_FALSE,
			.polygonMode = vk::PolygonMode::eFill,
			.cullMode = vk::CullModeFlagBits::eBack,
			.frontFace = vk::FrontFace::eClockwise,
			.depthBiasEnable = VK_FALSE,
			.lineWidth = 1.0f,
		};

		// TODO: Expose multisampling options
		vk::PipelineMultisampleStateCreateInfo info_multisampling{
			.rasterizationSamples = vk::SampleCountFlagBits::e1,
			.sampleShadingEnable = VK_FALSE,
		};

		// TODO: Expose colour blending options.
		vk::PipelineColorBlendAttachmentState colour_blend_attachment{
			.blendEnable = VK_FALSE,
			.colorWriteMask
				= vk::ColorComponentFlagBits::eR
				| vk::ColorComponentFlagBits::eG
				| vk::ColorComponentFlagBits::eB
				| vk::ColorComponentFlagBits::eA
		};

		const std::array attachments{ colour_blend_attachment };

		vk::PipelineColorBlendStateCreateInfo info_colour_blending{
			.logicOpEnable = VK_FALSE,
			.logicOp = vk::LogicOp::eCopy,
			.attachmentCount = static_cast<uint32_t>(attachments.size()),
			.pAttachments = attachments.data(),
			.blendConstants = std::array{ 0.0f, 0.0f, 0.0f, 0.0f },
		};

		// TODO: Extract the layout description from the shader. spriv-cross / spriv-reflection
		/*descriptor::Layout::Description descriptor_layout{
			.bindings = {
				{
					vk::DescriptorType::eUniformBuffer,
					Shader::Stage::Vertex,
				},
			},
		};*/
		// Load the layout from a cache.
		//descriptor = descriptor_layout;
		const std::array<vk::DescriptorSetLayout, 0> descriptors;
		const std::array<vk::PushConstantRange, 0> push_constants;

		// TODO: Extract to base to share with compute shader
		vk::PipelineLayoutCreateInfo info_layout{
			.setLayoutCount = static_cast<uint32_t>(descriptors.size()),
			.pSetLayouts = descriptors.data(),
			.pushConstantRangeCount = static_cast<uint32_t>(push_constants.size()),
			.pPushConstantRanges = push_constants.data(),
		};

		std::vector<vk::PipelineShaderStageCreateInfo> info_stages; info_stages.reserve(stages.size());
		for (const auto& shader : stages) {
			info_stages.emplace_back(vk::PipelineShaderStageCreateInfo{
				.stage = meta::enm::to<vk::ShaderStageFlagBits>(shader.stage),
				.module = shader.self,
				// TODO: Expose entry point
				.pName = "main",
				.pSpecializationInfo = {},
			});
		}

		layout = nova_abyss_api->dev.createPipelineLayout(info_layout, nova_abyss_api->alloc);

		vk::GraphicsPipelineCreateInfo info_pipeline{
			.stageCount = static_cast<uint32_t>(info_stages.size()),
			.pStages = info_stages.data(),
			.pVertexInputState = &info_input_vertex,
			.pInputAssemblyState = &info_input_assembly,
			.pTessellationState = {},
			.pViewportState = &info_viewport,
			.pRasterizationState = &info_rasterizer,
			.pMultisampleState = &info_multisampling,
			.pDepthStencilState = {}, // TODO: Depth Stencil
			.pColorBlendState = &info_colour_blending,
			//.pDynamicState = nullptr, // TODO: Dynamic State

			.layout = layout,
			.renderPass = renderpass,
			.subpass = 0, // TODO: expose subpass index to the constructor

			// TODO: Pipeline inheritance
			//.basePipelineHandle,
			//.basePipelineIndex,
		};

		self = NVK_CHECK(nova_abyss_api->dev.createGraphicsPipeline({}, info_pipeline, nova_abyss_api->alloc).value, "Failed to create Graphics Pipeline!");
		nova_bark_warn("Creation information!");
	}

	Graphics::~Graphics() {
		// FIXME: Objects should not prevent the GPU from going brr.
		// The objects requiring the barrier should be explicitly queued.
		nova_abyss_api->queues.graphics.self.waitIdle();
	}

}

#endif // NOVA_ABYSS_VULKAN
