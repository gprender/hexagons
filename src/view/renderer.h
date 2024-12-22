#pragma once

/**
 * @author Graeme Prendergast
 */

#include <memory>

#include "../config.h"
#include "shader.h"
#include "cube_mesh.h"
#include "texture.h"
#include "../model/scene.h"


class Renderer 
{
public:
    Renderer(GLFWwindow* window);
    ~Renderer();

    void render(Scene& scene);

private:
    void set_up_opengl(GLFWwindow* window);
    void make_assets();

    std::shared_ptr<CubeMesh> cube_mesh;
    std::shared_ptr<Texture> cube_texture;
    GLFWwindow* window;
    std::shared_ptr<Shader> shader;

    OpenGlId model_location;
    OpenGlId view_location;
};
