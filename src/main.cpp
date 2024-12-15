/**
 * @author Graeme Prendergast 
 */

#include "config.h"

#include "shader.h"
#include "triangle_mesh.h"
#include "material.h"

#include "camera.h"
#include "cube.h"


GLFWwindow* set_up_glfw() 
{
    GLFWwindow* window;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(640, 480, "Hexagons!", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    return window;
}

void set_up_opengl(GLFWwindow* window)
{
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    //Set the rendering region to the actual screen size
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    glViewport(0/*left*/, 0/*top*/, w, h);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW failed to start!\n";
        return -1;
    }
    GLFWwindow* window = set_up_glfw();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD failed to run its loader!\n";
        glfwTerminate();
        return -1;
    }

    set_up_opengl(window);

    // make the object(s) we want to render
    Cube cube({3.0f, 0.0f, 0.25f}, {0.25f, 0.25f, 0.25f});
    Camera camera({ 0.0f, 0.0f, 1.0f });

    // make the shader program
    std::vector<ShaderFileInfo> shader_infos 
    {
        { "src/shaders/vertex.glsl", GL_VERTEX_SHADER },
        { "src/shaders/fragment.glsl", GL_FRAGMENT_SHADER }
    };
    Shader shader(shader_infos);
    glUseProgram(shader.get_id());

    // configure the shader program
    OpenGlId view_location = glGetUniformLocation(shader.get_id(), "view");
    OpenGlId projection_location = glGetUniformLocation(shader.get_id(), "projection");

    glm::mat4 projection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

    while (!glfwWindowShouldClose(window))
    {
        // Keyboard events
        glm::vec3 dPos { 0.0f, 0.0f, 0.0f };
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        {
            dPos.x += 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        {
            dPos.y -= 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            dPos.x -= 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        {
            dPos.y += 1.0f;
        }
        if (glm::length(dPos) > 0.1f) 
        {
            dPos = glm::normalize(dPos);
            camera.move(dPos);
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        {
            break;
        }

        // Mouse events
        glm::vec3 dEulers { 0.0f, 0.0f, 0.0f };
        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        glfwSetCursorPos(window, 320.0, 240.0);
        glfwPollEvents();

        dEulers.z = -0.01f * static_cast<float>(mouse_x - 320.0);
        dEulers.y = -0.01f * static_cast<float>(mouse_y - 240.0);

        camera.spin(dEulers);

        cube.update(16.67f / 1000.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.get_id());
        glUniformMatrix4fv(
            view_location, 1, GL_FALSE, 
            glm::value_ptr(camera.get_view_transform()));
        cube.draw(shader.get_id());
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

