/**
 * @author Graeme Prendergast
 */

#include "app.h"


App::App()
{
    set_up_glfw();
}

App::~App() 
{
    glfwTerminate();
}

void App::set_up_opengl()
{
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    //Set the rendering region to the actual screen size
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0/*left*/, 0/*top*/, width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    std::vector<ShaderFileInfo> shader_infos {
        { "src/shaders/vertex.glsl", GL_VERTEX_SHADER },
        { "src/shaders/fragment.glsl", GL_FRAGMENT_SHADER }
    };
    shader_program = std::make_shared<Shader>(shader_infos);
    shader = shader_program->get_id();

    glUseProgram(shader);
    OpenGlId projection_location = glGetUniformLocation(shader, "projection");
    glm::mat4 projection(glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 10.0f));
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
}

void App::make_systems()
{
    motion_system = std::make_shared<MotionSystem>();
    camera_system = std::make_shared<CameraSystem>(shader, window);
    render_system = std::make_shared<RenderSystem>(shader, window);
}

void App::run() 
{
    while (!glfwWindowShouldClose(window)) 
    {
        motion_system->update(transform_components, physics_components);

        bool should_close = camera_system->update(transform_components, camera_id, *camera_component);
        if (should_close) break;

        render_system->update(transform_components, render_components);
    }
}

void App::set_up_glfw() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(640, 480, "Hello Window!", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Couldn't load opengl" << std::endl;
        glfwTerminate();
    }
}
