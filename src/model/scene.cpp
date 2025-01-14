/**
 * @author Graeme Prendergast
 */

#include "scene.h"


Scene::Scene():
    camera(
        {  0.0f, 0.0f, 5.0f }, // position
        {  0.0f, -90.0f, 90.0f } // rotation
    )
{
    objects.emplace_back(glm::vec3{ 0.0f, 0.0f, 0.0f });
}

void Scene::update(glm::vec3 const rotation_delta) 
{
    for (auto& object : objects)
    {
        object.update(rotation_delta);
    }
}

void Scene::move_camera(glm::vec3 const& position_delta)
{
    camera.move(position_delta);
}

void Scene::spin_camera(glm::vec3 const& rotation_delta)
{
    camera.spin(rotation_delta);
}