#version 330 core

layout (location = 0) in vec2 vertex_position;
layout (location = 1) in vec3 vertex_colour;

out vec3 fragment_colour;

//const vec3 colours[3] = vec3[]
//(
//	vec3(1.0, 0.0, 0.0),  // red
//	vec3(0.0, 1.0, 0.0),  // green
//	vec3(0.0, 0.0, 1.0)   // blue
//);

void main()
{
	gl_Position = vec4(vertex_position, 0.0, 1.0);
	fragment_colour = vertex_colour;
}
