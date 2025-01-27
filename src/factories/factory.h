/**
* @author Graeme Prendergast
*/

#pragma once

#include "../config.h"

#include "../components/camera_component.h"
#include "../components/physics_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"

#include <vector>
#include <unordered_map>


class EntityFactory
{
public:
	EntityFactory(
		TransformComponentMap_t& transform_components, 
		PhysicsComponentMap_t& physics_components,
		RenderComponentMap_t& render_components);

	~EntityFactory();

	EntityId make_camera(glm::vec3 const position, glm::vec3 const rotation);

	EntityId make_hexagon(
		glm::vec3 const position, 
		glm::vec3 const rotation,
		glm::vec3 const positional_velocity,
		glm::vec3 const rotational_velocity);

private:
	uint32_t entity_count = 0;
	EntityId generate_entity_id();

	TransformComponentMap_t& transform_components;
	PhysicsComponentMap_t& physics_components;
	RenderComponentMap_t& render_components;

	std::vector<OpenGlId> vertex_arrays;
	std::vector<OpenGlId> vertex_buffers;
	std::vector<OpenGlId> textures;

	RenderComponent make_render_component(
		std::string const& obj_filepath,
		std::string const& texture_filepath,
		glm::mat4 const pretransform = glm::mat4(1.0f));

	OpenGlId make_texture(std::string const& filepath);
};