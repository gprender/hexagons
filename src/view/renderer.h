/**
 * @author Graeme Prendergast
 */

#pragma once

#include "../config.h"
#include "shader.h"
#include "texture.h"
#include "../model/scene.h"
#include "PolygonMesh.h"

#include <memory>


class Renderer 
{
public:
    Renderer(GLFWwindow* window);
    ~Renderer();

    void render(Scene& scene);

private:
    void set_up_opengl(GLFWwindow* window);
    void make_assets();

    std::shared_ptr<PolygonMesh> default_mesh;
    std::shared_ptr<Texture> default_texture;

    GLFWwindow* window;
    std::shared_ptr<Shader> shader;

    OpenGlId model_location;
    OpenGlId view_location;
};
