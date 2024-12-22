#pragma once

#include "../config.h"


class Texture 
{
public:
	Texture(std::string const& filename);
	~Texture();
	void use();

private:
	OpenGlId texture;
};
