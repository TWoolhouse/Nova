#pragma once
#include "meta/head.h"
#include "spirv.h"

#include "abyss/shader.h"

namespace Nova::abyss::spirv {

	Binary compile(const std::filesystem::path& file, const Shader::Stage stage);
	Binary compile(const std::filesystem::path& ifile, const std::filesystem::path& ofile);

	Binary file(const std::filesystem::path& shader_file);
	Binary file(const std::filesystem::path& shader_file, const Shader::Stage type);

}
