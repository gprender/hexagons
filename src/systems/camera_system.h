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
		TransformComponent& camera_transform,
		CameraComponent& camera_component, 
		float const scalar = 0.015f);

private:
	OpenGlId view_location;
	glm::vec3 const global_up { 0.0f, 0.0f, 1.0f };
	GLFWwindow* window;

	void update_orientation_vectors(
		TransformComponent& camera_transform, 
		CameraComponent& camera_component);

	void update_position(
		TransformComponent& camera_transform, 
		CameraComponent& camera_component,
		float const scalar);

	void update_rotation(TransformComponent& camera_transform);

	void set_view(
		TransformComponent& camera_transform, 
		CameraComponent& camera_component) const;
};
