/**
* @author Graeme Prendergast 
*/

#include "render_system.h"


RenderSystem::RenderSystem(OpenGlId shader, GLFWwindow* window):
	model_location(glGetUniformLocation(shader, "model")),
	window(window)
{ }

void RenderSystem::update(
	std::unordered_map<EntityId, TransformComponent>& transform_components, 
	std::unordered_map<EntityId, RenderComponent>& render_components
) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto const& [id, renderable] : render_components)
	{
		auto const& transform = transform_components.at(id);

		glm::mat4 model(1.0f);
		model = glm::translate(model, transform.position);

		model = glm::rotate(model, glm::radians(transform.rotation.x), { 1.0f, 0.0f, 0.0f });
		model = glm::rotate(model, glm::radians(transform.rotation.y), { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, glm::radians(transform.rotation.z), { 0.0f, 0.0f, 1.0f });

		glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

		glBindTexture(GL_TEXTURE_2D, renderable.texture);
		glBindVertexArray(renderable.vertex_array);

		glDrawArrays(GL_TRIANGLES, 0, renderable.vertex_count);
	}

	glfwSwapBuffers(window);
}
