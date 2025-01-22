/**
* @author Graeme Prendergast 
*/

#pragma once

#include "../config.h"
#include "../components/transform_component.h"
#include "../components/physics_component.h"

#include <unordered_map>


class MotionSystem
{
public:
	void update(
		std::unordered_map<EntityId, TransformComponent>& transform_components,
		std::unordered_map<EntityId, PhysicsComponent>& physics_components,
		float const scalar = 1.0
	);
};
