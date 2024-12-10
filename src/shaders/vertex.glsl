#version 330 core

layout (location = 0) in vec3 vertex_position;

out vec2 fragment_texture_coordinates;

uniform mat4 model;
uniform mat4 view;

void main()
{
	gl_Position = view * model * vec4(vertex_position, 1.0);
	fragment_texture_coordinates = (0.5, -0.5) * (vertex_position.xy + vec2(1.0));
	// fragment_texture_coordinates = vertex_position.xy;  // cursed version
}
