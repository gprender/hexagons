#version 330 core

in vec3 fragment_colour;
in vec2 fragment_texture_coordinates;

out vec4 screen_colour;

uniform sampler2D material;

void main()
{
	screen_colour = texture(material, fragment_texture_coordinates);
}
