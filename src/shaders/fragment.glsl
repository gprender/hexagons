#version 330 core

in vec3 fragment_colour;
in vec2 fragment_texture_coordinates;

out vec4 screen_colour;

uniform sampler2D material;

void main()
{
	//vec3 base_colour = texture(material, fragment_texture_coordinates).rgb;
	//screen_colour = vec4(base_colour, 1.0);
	screen_colour = texture(material, fragment_texture_coordinates);
}
