/**
 * @author Graeme Prendergast 
 */

#include "config.h"
#include "shader.h"
#include "triangle_mesh.h"
#include "material.h"
#include "linear_algebra.h"


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
    glUseProgram(shader.get_id());
    
    OpenGlId model_location = glGetUniformLocation(shader.get_id(), "model");
    OpenGlId view_location = glGetUniformLocation(shader.get_id(), "view");

    vec3 const camera_position { -0.4f, 0.0f, 0.2f };
    vec3 const camera_target { 0.0f, 0.0f, 0.0f };

    mat4 view = create_look_at(camera_position, camera_target);
    // mat4 view = create_identity4();
    glUniformMatrix4fv(view_location, 1, GL_FALSE, view.entries);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        mat4 X = create_rotation_x(80 * glfwGetTime());
        mat4 Y = create_rotation_y(80 * glfwGetTime());
        mat4 Z = create_rotation_z(80 * glfwGetTime());

        mat4 model = Z;
        glUniformMatrix4fv(model_location, 1, GL_FALSE, model.entries);

        glClear(GL_COLOR_BUFFER_BIT);
        
        material.use();
        triangle.draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

