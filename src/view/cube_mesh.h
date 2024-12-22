#pragma once

#include "../config.h"


class CubeMesh
{
public:
    CubeMesh(glm::vec3 const size);
    ~CubeMesh();
    void draw();

private:
    OpenGlId vertex_array;
    OpenGlId vertex_buffer;

    void make_mesh(float const length, float const width, float const height);
};
