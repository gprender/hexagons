/**
* @author Graeme Prendergast 
*/

#include "motion_system.h"


void MotionSystem::update(
	std::unordered_map<EntityId, TransformComponent>& transform_components, 
	std::unordered_map<EntityId, PhysicsComponent>& physics_components, 
	float const scalar
) {
	for (auto const& [id, physics_component] : physics_components)
	{
		transform_components[id].position += physics_component.positional_velocity * scalar;

		transform_components[id].rotation = glm::mod(
			transform_components[id].rotation + physics_component.rotational_velocity * scalar, 
			360.0f
		);
	}
}
