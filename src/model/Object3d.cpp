/**
* @author Graeme Prendergast 
*/

#include "Object3d.h"


Object3d::Object3d(glm::vec3 const position):
	position(position)
{ }

void Object3d::update(glm::vec3 const rotation_delta)
{
	rotation = glm::mod(rotation + rotation_delta, 360.0f);
}

glm::mat4 Object3d::get_model_transform()
{
	glm::mat4 model(1.0f);

	model = glm::translate(model, position);

	model = glm::rotate(model, glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f });
	model = glm::rotate(model, glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f });
	model = glm::rotate(model, glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });

	return model;
}
