/**
 * @author Graeme Prendergast
 */

#pragma once

#include "../config.h"
#include "../model/scene.h"
#include "../view/renderer.h"


class App 
{
public:
    App();
    ~App();

    void run();

private:
    bool handle_input();
    void set_up_glfw();

    
    Scene scene;
    GLFWwindow* window;
    std::shared_ptr<Renderer> renderer;
};
