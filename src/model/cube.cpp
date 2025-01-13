#include "cube.h"
#include "stb/stb_image.h"


Cube::Cube(glm::vec3 const position):
    position(position)
{ }

void Cube::update(glm::vec3 const rotation_delta)
{
    rotation = glm::mod(rotation + rotation_delta, 360.0f);
}

glm::mat4 Cube::get_model_transform()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f });
    model = glm::rotate(model, glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f });
    model = glm::rotate(model, glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });

    return model;
}
