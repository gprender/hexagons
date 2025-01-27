/**
 * @author Graeme Prendergast
 */

#pragma once

#include "../config.h"

#include "../components/camera_component.h"
#include "../components/physics_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"

#include "../systems/camera_system.h"
#include "../systems/motion_system.h"
#include "../systems/render_system.h"

#include "../view/shader.h"

#include <unordered_map>
#include <memory>


class App 
{
public:
    App();
    ~App();

    void set_up_opengl(); // should these be private?
    void make_systems(); // ^^
    void run();

    std::unordered_map<OpenGlId, TransformComponent> transform_components;
    std::unordered_map<OpenGlId, PhysicsComponent> physics_components;
    std::unordered_map<OpenGlId, RenderComponent> render_components;

    std::shared_ptr<CameraComponent> camera_component;
    OpenGlId camera_id;

private:
    void set_up_glfw();

    GLFWwindow* window;

    std::shared_ptr<Shader> shader_program;
    OpenGlId shader;

    std::shared_ptr<MotionSystem> motion_system;
    std::shared_ptr<CameraSystem> camera_system;
    std::shared_ptr<RenderSystem> render_system;
};
