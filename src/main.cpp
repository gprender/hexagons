/**
 * @author Graeme Prendergast 
 */

#include "config.h"
#include "shader.h"


int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW failed to start!\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "hello window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);

    std::vector<ShaderFileInfo> shader_infos 
    {
        { "src/shaders/vertex.txt", GL_VERTEX_SHADER },
        { "src/shaders/fragment.txt", GL_FRAGMENT_SHADER }
    };
    Shader shader(shader_infos);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader.get_id());
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

