/**
* @author Graeme Prendergast
*/

#include "factory.h"

#include "../utilities/ObjReader.h"
#include "stb/stb_image.h"


EntityFactory::EntityFactory(
		TransformComponentMap_t& transform_components, 
		PhysicsComponentMap_t& physics_components, 
		RenderComponentMap_t& render_components):
	transform_components(transform_components),
	physics_components(physics_components),
	render_components(render_components)
{ }

EntityFactory::~EntityFactory()
{
	glDeleteVertexArrays(vertex_arrays.size(), vertex_arrays.data());
	glDeleteBuffers(vertex_buffers.size(), vertex_buffers.data());
	glDeleteTextures(textures.size(), textures.data());
}

EntityId EntityFactory::generate_entity_id()
{
	return entity_count++;
}

EntityId EntityFactory::make_camera(glm::vec3 const position, glm::vec3 const rotation)
{
	EntityId const entity_id = generate_entity_id();

	transform_components.emplace(entity_id, TransformComponent{ position, rotation });

	return entity_id;
}

EntityId EntityFactory::make_hexagon(
	glm::vec3 const position, 
	glm::vec3 const rotation,
	glm::vec3 const positional_velocity,
	glm::vec3 const rotational_velocity) 
{
	EntityId const entity_id = generate_entity_id();

	transform_components.emplace(entity_id, TransformComponent{ position, rotation });

	physics_components.emplace(entity_id, PhysicsComponent{ positional_velocity, rotational_velocity });

	static glm::mat4 const blender_pretransform = glm::rotate(
		glm::mat4(1.0f), glm::radians(90.0f), glm::vec3{1.0f, 0.0f, 0.0f});

	RenderComponent render_component = make_render_component(
		"assets/meshes/hexagonal_tile_tr.obj", 
		"assets/textures/ainsley.jpg", 
		blender_pretransform);

	render_components.emplace(entity_id, render_component);

	return entity_id;
}

std::vector<EntityId> EntityFactory::make_hexagonal_grid(int const nrows, int const ncolumns)
{
	static float const dX = glm::sqrt(3);
	static float const dx = dX / 2;
	static float const dy = 1.5;

	std::vector<EntityId> foo;
	foo.reserve(nrows * ncolumns);

	for (int row = 0; row < nrows; row++)
	{
		for (int column = 0; column < ncolumns; column++)
		{
			make_hexagon(
				glm::vec3{ 
					(column * dX) + ((row % 2) * dx), 
					(row * dy), 
					0.0f },
				glm::vec3(0.0f),
				glm::vec3(0.0f),
				glm::vec3(0.0f));
		}
	}

	return foo;
}

RenderComponent EntityFactory::make_render_component(
	std::string const& obj_filepath, 
	std::string const& texture_filepath, 
	glm::mat4 const pretransform)
{
	// read vertices from obj file
	std::vector<float> vertices;
	ObjReader::read_obj_mesh(obj_filepath, vertices, pretransform);
	uint32_t const vertex_count = vertices.size() / 8;

	// make vertex array
	OpenGlId vertex_array = 0;
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);
	vertex_arrays.push_back(vertex_array);

	// make vertex buffer
	OpenGlId vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	vertex_buffers.push_back(vertex_buffer);

	// position (vec3)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coordinates (vec2)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// normals (vec3)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)((3 + 2) * sizeof(float)));
	glEnableVertexAttribArray(2);

	// make texture
	OpenGlId texture = make_texture(texture_filepath);

	return RenderComponent{ vertex_array, texture, vertex_count };
}

OpenGlId EntityFactory::make_texture(std::string const& filepath)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	// make texture
	OpenGlId texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	textures.push_back(texture);

	// send data to gpu
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	// configure sampler
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}
