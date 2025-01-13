#version 330 core

in vec2 fragment_texture_coordinates;
in vec3 fragment_normal;

out vec4 screen_colour;

uniform sampler2D material;

const vec3 sun_direction = normalize(vec3(-1, 1.0, 1.0));

void main()
{
	float light_strength = max(0.2, dot(fragment_normal, sun_direction));
	screen_colour = vec4(light_strength * texture(material, fragment_texture_coordinates));
}
