#pragma once

#include "config.h"

/**
 * @author Graeme Prendergast
 */

struct ShaderFileInfo
{
	std::string filepath;
	OpenGlId shader_type;
};

std::string get_shader_log(OpenGlId shader);

bool check_shader_status_successful(OpenGlId shader, OpenGlId status_type);

class ShaderModule
{
public:
	ShaderModule(std::string const& filepath, OpenGlId module_type);

	~ShaderModule();

	inline OpenGlId get_id() const { return id; }

private:
	OpenGlId id;
};

class Shader
{
public:
	Shader(std::vector<ShaderFileInfo> file_infos);

	~Shader();

	inline OpenGlId get_id() const { return id; }

private:
	OpenGlId id;
};
