#pragma once

#include "../config.h"
#include "cube.h"
#include "camera.h"


class Scene 
{
public:
    Scene();

    void update(float const delta_rotation);
    void move_camera(glm::vec3 const& delta_position);
    void spin_camera(glm::vec3 const& delta_rotation);

    std::vector<Cube> cubes;
    Camera camera;
};