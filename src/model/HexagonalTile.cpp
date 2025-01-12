/**
* @author Graeme Prendergast 
*/

#include "HexagonalTile.h"


HexagonalTile::HexagonalTile(glm::vec3 const position):
	position(position)
{ }

void HexagonalTile::update(float const delta_rotation)
{
	rotation += delta_rotation;
	if (rotation.z > 360)
	{
		rotation.z -= 360;
	}
}

glm::mat4 HexagonalTile::get_model_transform()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });

	return model;
}
