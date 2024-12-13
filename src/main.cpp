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
    glUseProgram(shader.get_id());
    
    OpenGlId model_location = glGetUniformLocation(shader.get_id(), "model");
    OpenGlId view_location = glGetUniformLocation(shader.get_id(), "view");
    OpenGlId projection_location = glGetUniformLocation(shader.get_id(), "projection");

    glm::vec3 quad_position { 0.0f, 0.0f, 0.0f };
    glm::vec3 const camera_position { -2.0f, 0.0f, 2.0f };
    glm::vec3 const camera_target { 0.0f, 0.0f, 0.0f };
    glm::vec3 const up_vector { 0.0f, 0.0f, 1.0f };

    glm::mat4 view = glm::lookAt(camera_position, camera_target, up_vector);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, quad_position);
        model = glm::rotate(model, (float)glfwGetTime(), up_vector);
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

        glClear(GL_COLOR_BUFFER_BIT);
        
        material.use();
        triangle.draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

