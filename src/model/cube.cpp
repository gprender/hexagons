#include "cube.h"
#include "stb/stb_image.h"


Cube::Cube(glm::vec3 const position):
    position(position)
{ }

void Cube::update(float const delta_rotation)
{
    rotation += delta_rotation;
    if (rotation.z > 360)  // is there a way to do this without a branch?
    {
        rotation.z -= 360;
    }
}

glm::mat4 Cube::get_model_transform()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });

    return model;
}
