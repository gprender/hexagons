#include "renderer.h"
#include <vector>


Renderer::Renderer(GLFWwindow* window)
{
	this->window = window;
	make_assets();
	set_up_opengl(window);
}

Renderer::~Renderer()
{
	glDeleteProgram(shader->get_id());
}

void Renderer::render(Scene& scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->use();

	glUniformMatrix4fv(
		view_location, 1, GL_FALSE, 
		glm::value_ptr(scene.camera.get_view_transform())
	);

	cube_texture->use();
	for (auto& cube : scene.cubes)
	{
		glUniformMatrix4fv(
			model_location, 1, GL_FALSE,
			glm::value_ptr(cube.get_model_transform())
		);
		cube_mesh->draw();
	}

	glfwSwapBuffers(window);
}

void Renderer::set_up_opengl(GLFWwindow* window)
{
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    //Set the rendering region to the actual screen size
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0/*left*/, 0/*top*/, width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glUseProgram(shader->get_id());

	model_location = glGetUniformLocation(shader->get_id(), "model");
	view_location = glGetUniformLocation(shader->get_id(), "view");
	OpenGlId projection_location = glGetUniformLocation(shader->get_id(), "projection");

	glm::mat4 projection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 10.0f);
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::make_assets()
{
	cube_mesh = std::make_shared<CubeMesh>(glm::vec3{ 0.25f, 0.25f, 0.25f });

	cube_texture = std::make_shared<Texture>("img/ainsley.jpg");

	shader = std::make_shared<Shader>(
		std::vector<ShaderFileInfo>	{
			{ "src/shaders/vertex.glsl", GL_VERTEX_SHADER },
			{ "src/shaders/fragment.glsl", GL_FRAGMENT_SHADER }
		}
	);
}