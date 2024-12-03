#pragma once

/**
 * @author Graeme Prendergast
 */

#include "config.h"


class TriangleMesh
{
public:
	TriangleMesh();

	~TriangleMesh();

	void draw();

private:
	std::vector<OpenGlId> vertex_buffers;
	OpenGlId vertex_array;
	OpenGlId element_buffer;
	int element_count;
};