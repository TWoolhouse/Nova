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
		/*auto vert_code = spirv::file("start/first/.vert", Shader::Type::Vertex);
		auto frag_code = spirv::file("start/first/.frag", Shader::Type::Fragment);

		auto vert = nvk(device).createShaderModule({
			{},
			vert_code.size() * sizeof(spirv::Binary::value_type),
			vert_code.data(),
			}, nvk(alloc));

		auto frag = nvk(device).createShaderModule({
			{},
			frag_code.size() * sizeof(spirv::Binary::value_type),
			frag_code.data(),
			}, nvk(alloc));

		vk::PipelineShaderStageCreateInfo vert_info{
			{},
			vk::ShaderStageFlagBits::eVertex,
			vert,
			"main"
		};

		vk::PipelineShaderStageCreateInfo frag_info{
			{},
			vk::ShaderStageFlagBits::eFragment,
			frag,
			"main"
		};*/

		Shader vert{ Shader::Type::Vertex, "start/first/.vert"sv };
		Shader frag{ Shader::Type::Fragment, "start/first/.frag"sv };

		const std::array<vk::PipelineShaderStageCreateInfo, 2> shader_create_info{
			vert,
			frag
		};

		vk::PipelineVertexInputStateCreateInfo vertex_input_info{
			{},
			{},
			{}
		};

		vk::PipelineInputAssemblyStateCreateInfo input_assembly{
			{},
			vk::PrimitiveTopology::eTriangleList,
			VK_FALSE
		};

		vk::Viewport viewport{
			0.0f,
			0.0f,
			static_cast<float>(App->swapchain.extent.width),
			static_cast<float>(App->swapchain.extent.height),
			0.0f,
			1.0f,
		};

		vk::Rect2D scissor{
			{ 0, 0 },
			App->swapchain.extent
		};

		const std::array viewports{ viewport };
		const std::array scissors{ scissor };

		vk::PipelineViewportStateCreateInfo viewport_state_info{
		{},
			viewports,
			scissors
		};

		vk::PipelineRasterizationStateCreateInfo rasterizer{
			{},
			VK_FALSE,
			VK_FALSE,
			vk::PolygonMode::eFill,
			vk::CullModeFlagBits::eBack,
			vk::FrontFace::eClockwise,
			VK_FALSE,
			{}, {}, {},
			1.0f
		};

		vk::PipelineMultisampleStateCreateInfo multisampling{
			{},
			vk::SampleCountFlagBits::e1,
			VK_FALSE
		};

		vk::PipelineColorBlendAttachmentState colour_blend_attachment{
			VK_FALSE,
			{}, {}, {}, {}, {}, {},
			vk::ColorComponentFlagBits::eR
				| vk::ColorComponentFlagBits::eG
				| vk::ColorComponentFlagBits::eB
				| vk::ColorComponentFlagBits::eA
		};

		const std::array attachments{ colour_blend_attachment };

		vk::PipelineColorBlendStateCreateInfo colour_blending{
			{},
			VK_FALSE,
			vk::LogicOp::eCopy,
			attachments,
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		};

		const std::array<vk::DescriptorSetLayout, 0> descriptors;
		const std::array<vk::PushConstantRange, 0> push_constants;

		vk::PipelineLayoutCreateInfo pipeline_layout_info{
			{},
			descriptors,
			push_constants
		};

		auto layout = nvk(device).createPipelineLayout(pipeline_layout_info, nvk(alloc));

		vk::GraphicsPipelineCreateInfo pipeline_info{
			{},
			shader_create_info,
			&vertex_input_info,
			&input_assembly,
			{},
			&viewport_state_info,
			&rasterizer,
			&multisampling,
			{},
			&colour_blending,
			{},
			layout,
			renderpass.pass,
			0
		};

		auto pipeline = nvk(device).createGraphicsPipeline({}, { pipeline_info }, nvk(alloc));

		return { layout, pipeline };

	}

}
