/**
 * @author Graeme Prendergast
 */

#include "shader.h"


std::string get_shader_log(OpenGlId shader)
{
	int log_length;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

	if (log_length < 1)
	{
		return "Failed to get shader log length";
	}

	std::vector<char> log_buffer;
	log_buffer.reserve(log_length);

	glGetShaderInfoLog(shader, log_length, NULL, log_buffer.data());

	std::string log_string(log_buffer.begin(), log_buffer.end());
	return log_string;
}

bool check_shader_status_successful(OpenGlId shader, OpenGlId status_type)
{
	int success;
	glGetShaderiv(shader, status_type, &success);

	if (!success)
	{
		std::cout << "Shader status error: " << get_shader_log(shader) << std::endl;
		return false;
	}

	return true;
}

ShaderModule::ShaderModule(std::string const& filepath, OpenGlId module_type)
{
	std::ifstream file;
	std::stringstream buffer;
	std::string line;

	file.open(filepath);
	while (std::getline(file, line))
	{
		buffer << line << std::endl;
	}

	std::string shader_source = buffer.str();
	const char* shader_source_cstr = shader_source.c_str();

	OpenGlId shader_module = glCreateShader(module_type);
	glShaderSource(shader_module, 1, &shader_source_cstr, NULL);
	glCompileShader(shader_module);

	check_shader_status_successful(shader_module, GL_COMPILE_STATUS);

	id = shader_module;
}

ShaderModule::~ShaderModule()
{
	glDeleteShader(id);
}

Shader::Shader(std::vector<ShaderFileInfo> file_infos)
{
	OpenGlId shader = glCreateProgram();

	for (auto const& file_info : file_infos)
	{
		ShaderModule module(file_info.filepath, file_info.shader_type);
		glAttachShader(shader, module.get_id());
	}
	
	glLinkProgram(shader);

	check_shader_status_successful(shader, GL_LINK_STATUS);

	id = shader;
}

Shader::~Shader()
{
	glDeleteProgram(id);
}
