#version 330 core

in vec3 fragment_colour;

out vec4 screen_colour;

void main()
{
	screen_colour = vec4(fragment_colour, 1.0);
}
