/**
 * @author Graeme Prendergast
 */

#pragma once

#include "../config.h"
#include "camera.h"
#include "Object3d.h"


class Scene 
{
public:
    Scene();

    void update(glm::vec3 const rotation_delta);
    void move_camera(glm::vec3 const& position_delta);
    void spin_camera(glm::vec3 const& rotation_delta);

    std::vector<Object3d> objects;
    Camera camera;
};