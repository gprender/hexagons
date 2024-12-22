/**
 * @author Graeme Prendergast
 */

#include "shader.h"

/*************************************************************
 * Shader */

Shader::Shader(std::vector<ShaderFileInfo> file_infos)
{
	OpenGlId shader = glCreateProgram();

	for (auto const& file_info : file_infos)
	{
		ShaderModule module(file_info.filepath, file_info.shader_type);
		glAttachShader(shader, module.get_id());
	}
	
	glLinkProgram(shader);

	check_shader_program_status(shader);

	id = shader;
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

bool Shader::check_shader_program_status(OpenGlId shader)
{
	int success = 0;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);

	if (!success)
	{
		std::cout << "Shader program status error: " << get_shader_program_log(shader) << std::endl;
		return false;
	}

	return true;
}

std::string Shader::get_shader_program_log(OpenGlId shader)
{
	int log_length = 0;
	glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &log_length);

	if (log_length < 1)
	{
		return "Failed to get shader program log length";
	}

	std::vector<char> log_buffer;
	log_buffer.resize(log_length);

	glGetShaderInfoLog(shader, log_length, NULL, log_buffer.data());

	std::string log_string(log_buffer.begin(), log_buffer.end());
	return log_string;
}

/*************************************************************
 * Shader Module */

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

	check_shader_module_status(shader_module);

	id = shader_module;
}

ShaderModule::~ShaderModule()
{
	glDeleteShader(id);
}

bool ShaderModule::check_shader_module_status(OpenGlId shader)
{
	int success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		std::cout << "Shader module status error: " << get_shader_module_log(shader) << std::endl;
		return false;
	}

	return true;
}

std::string ShaderModule::get_shader_module_log(OpenGlId shader)
{
	int log_length = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

	if (log_length < 1)
	{
		return "Failed to get shader module log length";
	}

	std::vector<char> log_buffer;
	log_buffer.resize(log_length);

	glGetShaderInfoLog(shader, log_length, NULL, log_buffer.data());

	std::string log_string(log_buffer.begin(), log_buffer.end());
	return log_string;
}
