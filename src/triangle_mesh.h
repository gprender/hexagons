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
	OpenGlId vertex_buffer;
	OpenGlId vertex_array;
	int vertex_count;
};