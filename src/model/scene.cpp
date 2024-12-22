#include "scene.h"

Scene::Scene():
    camera({ 0.0f, 0.0f, 1.0f })
{
    cubes.emplace_back(glm::vec3{ 3.0f, 0.0f, 0.25f });
}

void Scene::update(float const delta_rotation) 
{
    for (auto& cube : cubes)
    {
        cube.update(delta_rotation);
    }
}

void Scene::move_camera(glm::vec3 const& delta_position)
{
    camera.move(delta_position);
}

void Scene::spin_camera(glm::vec3 const& delta_rotation)
{
    camera.spin(delta_rotation);
}