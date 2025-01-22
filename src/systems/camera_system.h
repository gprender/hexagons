/**
* @author Graeme Prendergast 
*/

#pragma once

#include "../config.h"
#include "../components/camera_component.h"
#include "../components/transform_component.h"

#include <unordered_map>


class CameraSystem
{
public:
	CameraSystem(OpenGlId shader, GLFWwindow* window);

	bool update(
		std::unordered_map<EntityId, TransformComponent>& transform_components,
		EntityId camera_id, 
		CameraComponent& camera_component, 
		float const scalar = 1.0f
	);

private:
	OpenGlId view_location;
	glm::vec3 const global_up = { 0.0f, 0.0f, 1.0f };
	GLFWwindow* window;
};
