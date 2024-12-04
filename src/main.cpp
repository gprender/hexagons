/**
 * @author Graeme Prendergast 
 */

#include "config.h"
#include "shader.h"
#include "triangle_mesh.h"
#include "material.h"


int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW failed to start!\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "hexagons", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD failed to run its loader!\n";
        glfwTerminate();
        return -1;
    }

    glClearColor(0.5f, 0.5f, 0.75f, 1.0f);

    TriangleMesh triangle;
    Material material("img/ainsley.jpg");

    std::vector<ShaderFileInfo> shader_infos 
    {
        { "src/shaders/vertex.glsl", GL_VERTEX_SHADER },
        { "src/shaders/fragment.glsl", GL_FRAGMENT_SHADER }
    };
    Shader shader(shader_infos);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader.get_id());
        material.use();
        triangle.draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

