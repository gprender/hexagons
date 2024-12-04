#version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in int colour_index;

out vec3 fragment_colour;
out vec2 fragment_texture_coordinates;

const vec3 colours[4] = vec3[]
(
	vec3(1.0, 0.0, 0.0),  // red
	vec3(0.0, 1.0, 0.0),  // green
	vec3(0.0, 0.0, 1.0),  // blue
	vec3(0.5, 0.5, 0.0)   // orange?
);

void main()
{
	gl_Position = vec4(vertex_position, 1.0);
	fragment_colour = colours[colour_index];
	fragment_texture_coordinates = vertex_position.xy;
}
