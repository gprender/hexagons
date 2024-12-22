#include "texture.h"
#include "stb/stb_image.h"


Texture::Texture(std::string const& filename)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	// make texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// send data to gpu
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	// configure sampler
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}
