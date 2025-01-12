/**
* @author Graeme Prendergast 
*/

#pragma once

#include "../config.h"


class Object3d
{
public:
    Object3d(glm::vec3 const position);
    void update(glm::vec3 const rotation_delta);
    glm::mat4 get_model_transform(); 

private:
    glm::vec3 position;
    glm::vec3 rotation { 0.0f, 0.0f, 0.0f };
};
