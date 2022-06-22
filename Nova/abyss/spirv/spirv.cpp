#include "npch.h"
#include "spirv_compile.h"

#include <shaderc/shaderc.hpp>
#include <abyss/vulkan/shader.h>

namespace Nova::abyss::spirv {

	const std::filesystem::path shader_src{ "shader" };
	const std::filesystem::path shader_bin{ "shader/bin" };

	constexpr shaderc_shader_kind shader_type(const vkn::Shader::Type type) {
		using namespace vkn;
		switch (type) {
			case Shader::Type::Vertex:	return shaderc_shader_kind::shaderc_glsl_default_vertex_shader;
			case Shader::Type::Fragment:	return shaderc_shader_kind::shaderc_glsl_default_fragment_shader;
			default:
				return shaderc_shader_kind::shaderc_glsl_infer_from_source;
		}
	}

	std::string read_src_file(const std::filesystem::path& file_path) {
		std::string text;
		std::ifstream file{ file_path };
		if (!file)	throw std::invalid_argument("Unable to Open File: "s + file_path.generic_string());
		text.reserve(std::filesystem::file_size(file_path) / sizeof(decltype(text)::value_type) + 1);
		text.assign(std::istreambuf_iterator<char>(file), {});
		return text;
	}
	Binary read_spv_file(const std::filesystem::path& file_path) {
		std::ifstream file{ file_path, std::ios::in | std::ios::ate | std::ios::binary };
		if (!file)	throw std::invalid_argument("Unable to Open File: "s + file_path.generic_string());
		const auto size = file.tellg();
		const auto fsize = std::filesystem::file_size(file_path);
		file.seekg(std::ios::beg);
		Binary buffer(std::ceil(size / static_cast<float>(sizeof(Binary::value_type))));
		file.read(reinterpret_cast<char*>(buffer.data()), size);
		return buffer;
	}

	Binary compile(const std::filesystem::path& file_path, const vkn::Shader::Type type) {
		const auto shader = read_src_file(file_path);
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		if constexpr (Nova::meta::def::Debug) {
			options.SetGenerateDebugInfo();
			options.SetOptimizationLevel(shaderc_optimization_level::shaderc_optimization_level_zero);
		}
		else {
			options.SetOptimizationLevel(shaderc_optimization_level::shaderc_optimization_level_performance);
		}
		const auto spv = compiler.CompileGlslToSpv(
			shader,
			shader_type(type),
			file_path.generic_string().c_str(),
			options
		);
		if (spv.GetNumErrors()) {
			nova_bark_error("Shader Compiliation[{}]<{}> {}", static_cast<std::underlying_type_t<decltype(spv.GetCompilationStatus())>>(spv.GetCompilationStatus()), file_path.generic_string(), spv.GetErrorMessage());
			throw std::runtime_error("Shader Compilation Error");
		}
		return { spv.cbegin(), spv.cend() };
	}

	Binary compile(const std::filesystem::path& ifile, const std::filesystem::path& ofile, const vkn::Shader::Type type) {
		nova_bark_info("Compiling Shader: {}", ifile.generic_string());
		auto binary = compile(ifile, type);
		std::filesystem::create_directories(ofile.parent_path());
		std::ofstream file{ ofile, std::ios::out | std::ios::binary };
		if (!file) throw std::invalid_argument("Unable to Open File:"s + ofile.generic_string());
		file.write(reinterpret_cast<char*>(binary.data()), binary.size() * sizeof(decltype(binary)::value_type));
		return binary;
	}

	Binary file(const std::filesystem::path& shader_file) {
		nova_bark_debug("Loading Shader: {}", shader_file.generic_string());
		const auto path_spv = shader_bin / shader_file;
		if (std::filesystem::exists(path_spv))
			return read_spv_file(path_spv);
		return spirv::compile(shader_src / shader_file, path_spv, vkn::Shader::Type::Default);
	}

	Binary file(const std::filesystem::path& shader_file, const vkn::Shader::Type type) {
		nova_bark_debug("Loading Shader: {}", shader_file.generic_string());
		const auto path_spv = shader_bin / shader_file;
		if (std::filesystem::exists(path_spv))
			return read_spv_file(path_spv);
		return spirv::compile(shader_src / shader_file, path_spv, type);
	}

}
