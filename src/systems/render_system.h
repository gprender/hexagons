/**
* @author Graeme Prendergast 
*/

#pragma once

#include "../config.h"
#include "../components/transform_component.h"
#include "../components/render_component.h"

#include <unordered_map>


class RenderSystem
{
public:
	RenderSystem(OpenGlId shader, GLFWwindow* window);

	void update(
		std::unordered_map<EntityId, TransformComponent>& transform_components,
		std::unordered_map<EntityId, RenderComponent>& render_components
	);

private:
	OpenGlId model_location;
	GLFWwindow* window;
};
