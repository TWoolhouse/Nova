#pragma once
#include "meta/head.h"
#include "spirv.h"
#include "abyss/vulkan/shader.h"

namespace Nova::abyss::spirv {

	Binary compile(const std::filesystem::path& file, const vkn::Shader::Type type);
	Binary compile(const std::filesystem::path& ifile, const std::filesystem::path& ofile);

	Binary file(const std::filesystem::path& shader_file);
	Binary file(const std::filesystem::path& shader_file, const vkn::Shader::Type type);

}
