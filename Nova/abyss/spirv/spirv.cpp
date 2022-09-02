#include "npch.h"
#include "spirv_compile.h"

#include <shaderc/shaderc.hpp>

using namespace std::string_literals;

nova_meta_enum_str(shaderc_compilation_status, status) {
	using Status = decltype(status);
	switch (status) {
		case Status::shaderc_compilation_status_success:	return "Sucess";
		case Status::shaderc_compilation_status_invalid_stage:	return "Invalid Stage";
		case Status::shaderc_compilation_status_compilation_error:	return "Compilation Error";
		case Status::shaderc_compilation_status_internal_error:	return "Internal Error";
		case Status::shaderc_compilation_status_null_result_object:	return "Null Result Object";
		case Status::shaderc_compilation_status_invalid_assembly:	return "Invalid Assembly";
		case Status::shaderc_compilation_status_validation_error:	return "Validation Error";
		case Status::shaderc_compilation_status_transformation_error:	return "Transformation Error";
		case Status::shaderc_compilation_status_configuration_error:	return "Configuration Error";
	default:
		nova_bark_warn("Unknown Case []: {}", static_cast<std::underlying_type_t<decltype(status)>>(status));
		return "Unknown";
	}
}

namespace Nova::abyss::spirv {

	const std::filesystem::path shader_src{ "shader" };
	const std::filesystem::path shader_bin{ "shader/bin" };

	constexpr shaderc_shader_kind shader_type(const Shader::Stage stage) {
		using namespace nvk;
		using Stage = decltype(stage);
		switch (stage) {
			case Stage::Vertex:	return shaderc_shader_kind::shaderc_glsl_default_vertex_shader;
			case Stage::Fragment:	return shaderc_shader_kind::shaderc_glsl_default_fragment_shader;
			default:
				nova_bark_warn("Unahndled Case [Shader Stage]: {}", stage);
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
		file.seekg(std::ios::beg);
		Binary buffer(std::ceil(size / static_cast<float>(sizeof(Binary::value_type))));
		file.read(reinterpret_cast<char*>(buffer.data()), size);
		return buffer;
	}

	Binary compile(const std::filesystem::path& file_path, const nvk::Shader::Stage stage) {
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
			shader_type(stage),
			file_path.generic_string().c_str(),
			options
		);
		if (spv.GetCompilationStatus() != shaderc_compilation_status::shaderc_compilation_status_success) {
			nova_bark_error("Shader Compiliation[{}]<{}> {}", spv.GetCompilationStatus(), file_path.generic_string(), spv.GetErrorMessage());
			throw std::runtime_error("Shader Compilation Error");		
		}
		nova_assert(std::distance(spv.cbegin(), spv.cend()) > 0, "Shader Code must have a length greater than 0!");
		return { spv.cbegin(), spv.cend() };
	}

	Binary compile(const std::filesystem::path& ifile, const std::filesystem::path& ofile, const nvk::Shader::Stage stage) {
		nova_bark_info("Compiling Shader: {}", ifile.generic_string());
		auto binary = compile(ifile, stage);
		std::filesystem::create_directories(ofile.parent_path());
		std::ofstream file{ ofile, std::ios::out | std::ios::binary };
		if (!file) throw std::invalid_argument("Unable to Open File:"s + ofile.generic_string());
		file.write(reinterpret_cast<char*>(binary.data()), binary.size() * sizeof(decltype(binary)::value_type));
		return binary;
	}

	Binary file(const std::filesystem::path& shader_file, const nvk::Shader::Stage stage) {
		nova_bark_debug("Loading Shader: {}", shader_file.generic_string());
		const auto path_spv = shader_bin / shader_file;
		if (std::filesystem::exists(path_spv))
			return read_spv_file(path_spv);
		return spirv::compile(shader_src / shader_file, path_spv, stage);
	}

}
