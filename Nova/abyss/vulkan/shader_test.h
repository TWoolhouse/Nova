#pragma once
#include "vk.h"
#include "app.h"
#include "renderpass.h"
#include "abyss/spirv/spirv_compile.h"
#include "shader.h"

namespace Nova::abyss::vkn {

	std::vector<char> read_shader(const std::string& path) {
		nova_bark_info("Reading Shader: {}", path);
		std::ifstream file(path, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		auto size = (size_t)file.tellg();
		std::vector<char> buffer(size);

		file.seekg(0);
		file.read(buffer.data(), size);

		file.close();

		return buffer;
	}

	std::pair<vk::PipelineLayout, vk::Pipeline> create_pipeline(RenderPass& renderpass) {
		nvk_tracec("Pipeline");

		Shader vert{ Shader::Type::Vertex, "start/first/.vert"sv };
		Shader frag{ Shader::Type::Fragment, "start/first/.frag"sv };

		const std::array<vk::PipelineShaderStageCreateInfo, 2> shader_create_info{
			vert,
			frag
		};

		vk::PipelineVertexInputStateCreateInfo vertex_input_info{
			.vertexBindingDescriptionCount = 0,
			.vertexAttributeDescriptionCount = 0,
		};

		vk::PipelineInputAssemblyStateCreateInfo input_assembly{
			.topology = vk::PrimitiveTopology::eTriangleList,
			.primitiveRestartEnable = VK_FALSE,
		};

		vk::Viewport viewport{
			.x = 0.0f,
			.y = 0.0f,
			.width = static_cast<float>(App->swapchain.extent.width),
			.height = static_cast<float>(App->swapchain.extent.height),
			.minDepth = 0.0f,
			.maxDepth = 1.0f,
		};

		vk::Rect2D scissor{
			.offset = { 0, 0 },
			.extent = App->swapchain.extent,
		};

		vk::PipelineViewportStateCreateInfo viewport_state_info{
			.viewportCount = 1,
			.pViewports = &viewport,
			.scissorCount = 1,
			.pScissors = &scissor,
		};

		vk::PipelineRasterizationStateCreateInfo rasterizer{
			.depthClampEnable = VK_FALSE,
			.rasterizerDiscardEnable = VK_FALSE,
			.polygonMode = vk::PolygonMode::eFill,
			.cullMode = vk::CullModeFlagBits::eBack,
			.frontFace = vk::FrontFace::eClockwise,
			.depthBiasEnable = VK_FALSE,
			.lineWidth = 1.0f,
		};

		vk::PipelineMultisampleStateCreateInfo multisampling{
			.rasterizationSamples = vk::SampleCountFlagBits::e1,
			.sampleShadingEnable = VK_FALSE,
		};

		vk::PipelineColorBlendAttachmentState colour_blend_attachment{
			.blendEnable = VK_FALSE,
			.colorWriteMask = vk::ColorComponentFlagBits::eR
				| vk::ColorComponentFlagBits::eG
				| vk::ColorComponentFlagBits::eB
				| vk::ColorComponentFlagBits::eA
		};

		const std::array attachments{ colour_blend_attachment };

		vk::PipelineColorBlendStateCreateInfo colour_blending{
			.logicOpEnable = VK_FALSE,
			.logicOp = vk::LogicOp::eCopy,
			.attachmentCount = static_cast<uint32_t>(attachments.size()),
			.pAttachments = attachments.data(),
			.blendConstants = std::array{ 0.0f, 0.0f, 0.0f, 0.0f },
		};

		const std::array<vk::DescriptorSetLayout, 0> descriptors;
		const std::array<vk::PushConstantRange, 0> push_constants;

		vk::PipelineLayoutCreateInfo pipeline_layout_info{
			.setLayoutCount = static_cast<uint32_t>(descriptors.size()),
			.pSetLayouts = descriptors.data(),
			.pushConstantRangeCount = static_cast<uint32_t>(push_constants.size()),
			.pPushConstantRanges = push_constants.data(),
		};

		auto layout = nvk(device).createPipelineLayout(pipeline_layout_info, nvk(alloc));

		vk::GraphicsPipelineCreateInfo pipeline_info{
			.stageCount = static_cast<uint32_t>(shader_create_info.size()),
			.pStages = shader_create_info.data(),
			.pVertexInputState = &vertex_input_info,
			.pInputAssemblyState = &input_assembly,
			.pViewportState = &viewport_state_info,
			.pRasterizationState = &rasterizer,
			.pMultisampleState = &multisampling,
			.pColorBlendState = &colour_blending,
			.layout = layout,
			.renderPass = renderpass.pass,
			.subpass = 0,
		};

		auto pipeline = nvk(device).createGraphicsPipeline({}, { pipeline_info }, nvk(alloc));

		return { layout, pipeline };

	}

}
