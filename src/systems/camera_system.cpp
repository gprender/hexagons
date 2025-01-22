/**
* @author Graeme Prendergast 
*/

#include "camera_system.h"

#include <cmath>


CameraSystem::CameraSystem(OpenGlId shader, GLFWwindow* window):
	view_location(glGetUniformLocation(shader, "view")),
	window(window)
{ }

bool CameraSystem::update(
	std::unordered_map<EntityId, TransformComponent>& transform_components, 
	EntityId camera_id, 
	CameraComponent& camera_component, 
	float const scalar = 1.0f
) {
	// build camera view matrix
	auto& camera_transform = transform_components.at(camera_id);
	float const theta = glm::radians(camera_transform.rotation.z);
	float const phi = glm::radians(camera_transform.rotation.y);

	glm::vec3& right = camera_component.relative_right;
	glm::vec3& up = camera_component.relative_up;
	glm::vec3& forwards = camera_component.relative_forwards;

	forwards = {
		glm::cos(theta) * glm::cos(phi),
		glm::sin(theta) * glm::cos(phi),
		glm::sin(phi)
	};
	right = glm::normalize(glm::cross(forwards, global_up));
	up = glm::normalize(glm::cross(right, forwards));

	glm::mat4 view = glm::lookAt(camera_transform.position, camera_transform.position + forwards, up);
	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

	// handle camera input

	// keys
	glm::vec3 position_delta { 0.0f, 0.0f, 0.0f };
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position_delta.x += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position_delta.y -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position_delta.x -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position_delta.y += 1.0f;

	if (glm::length(position_delta) > 0.1f) 
	{
		// update camera position
		position_delta = glm::normalize(position_delta);
		camera_transform.position += (0.1f * position_delta.x * forwards);
		camera_transform.position += (0.1f * position_delta.y * right);
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		// exit
		return true;
	}

	// mouse
	glm::vec3 rotation_delta { 0.0f, 0.0f, 0.0f };
	double mouse_x, mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	glfwSetCursorPos(window, 320.0, 240.0);
	glfwPollEvents();

	rotation_delta.z = -0.1f * static_cast<float>(mouse_x - 320.0);
	rotation_delta.y = -0.1f * static_cast<float>(mouse_y - 240.0);

	camera_transform.rotation.y = fminf(89.0f, fmaxf(-89.0f, camera_transform.rotation.y + rotation_delta.y));

	camera_transform.rotation.z = std::fmod(camera_transform.rotation.z + rotation_delta.z, 360.0);

	return false;
}
