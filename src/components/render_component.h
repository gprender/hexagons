/**
* @author Graeme Prendergast 
*/

#pragma once

#include "../config.h"


struct RenderComponent
{
	OpenGlId vertex_array;
	OpenGlId texture;
	uint32_t vertex_count;
};
