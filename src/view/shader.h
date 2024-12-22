/**
 * @author Graeme Prendergast
 */

#pragma once

#include "../config.h"


struct ShaderFileInfo
{
	std::string filepath;
	OpenGlId shader_type;
};

class Shader
{
public:
	Shader(std::vector<ShaderFileInfo> file_infos);
	~Shader();

	inline OpenGlId get_id() const { return id; }
	inline void use() const { glUseProgram(id); }

private:
	OpenGlId id;

	std::string get_shader_program_log(OpenGlId shader);
	bool check_shader_program_status(OpenGlId shader);
};

class ShaderModule
{
public:
	ShaderModule(std::string const& filepath, OpenGlId module_type);
	~ShaderModule();

	inline OpenGlId get_id() const { return id; }

private:
	OpenGlId id;

	std::string get_shader_module_log(OpenGlId shader);
	bool check_shader_module_status(OpenGlId shader);
};


