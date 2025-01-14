#include "camera.h"


Camera::Camera(glm::vec3 const position, glm::vec3 const rotation):
	position(position),
	rotation(rotation)
{ }

glm::mat4 Camera::get_view_transform()
{
	float theta = glm::radians(rotation.z);
	float phi = glm::radians(rotation.y);

	forwards = {
		glm::cos(theta) * glm::cos(phi),
		glm::sin(theta) * glm::cos(phi),
		glm::sin(phi)
	};
	right = glm::normalize(glm::cross(forwards, global_up));
	up = glm::normalize(glm::cross(right, forwards));;

	return glm::lookAt(position, position + forwards, up);
}

void Camera::move(glm::vec3 const dPos)
{
	position += 0.001f * dPos.x * forwards;
	position += 0.001f * dPos.y * right;
	position += 0.001f * dPos.z * up;
}

void Camera::spin(glm::vec3 const dEulers)
{
	rotation.y = fminf(89.0f, fmaxf(-89.0f, rotation.y + dEulers.y));

	rotation.z += dEulers.z;
	if (rotation.z > 360) {
		rotation.z -= 360;
	}
	else if (rotation.z < 0) {
		rotation.z += 360;
	}
}
