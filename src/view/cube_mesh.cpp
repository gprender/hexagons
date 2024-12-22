#include "cube_mesh.h"


CubeMesh::CubeMesh(glm::vec3 const size)
{
	make_mesh(size.x, size.y, size.z);
}

CubeMesh::~CubeMesh()
{
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array);
}

void CubeMesh::draw()
{
    glBindVertexArray(vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeMesh::make_mesh(float const length, float const width, float const height)
{
    std::vector<float> vertices {
        length,  width, -height, 1.0f, 1.0f,
        length, -width, -height, 1.0f, 0.0f,
        -length, -width, -height, 0.0f, 0.0f,
        -length, -width, -height, 0.0f, 0.0f,
        -length,  width, -height, 0.0f, 1.0f,
        length,  width, -height, 1.0f, 1.0f,

        -length, -width,  height, 0.0f, 0.0f,
        length, -width,  height, 1.0f, 0.0f,
        length,  width,  height, 1.0f, 1.0f,
        length,  width,  height, 1.0f, 1.0f,
        -length,  width,  height, 0.0f, 1.0f,
        -length, -width,  height, 0.0f, 0.0f,

        -length,  width,  height, 1.0f, 1.0f,
        -length,  width, -height, 1.0f, 0.0f,
        -length, -width, -height, 0.0f, 0.0f,
        -length, -width, -height, 0.0f, 0.0f,
        -length, -width,  height, 0.0f, 1.0f,
        -length,  width,  height, 1.0f, 1.0f,

        length, -width, -height, 0.0f, 0.0f,
        length,  width, -height, 1.0f, 0.0f,
        length,  width,  height, 1.0f, 1.0f,
        length,  width,  height, 1.0f, 1.0f,
        length, -width,  height, 0.0f, 1.0f,
        length, -width, -height, 0.0f, 0.0f,

        -length, -width, -height, 0.0f, 0.0f,
        length, -width, -height, 1.0f, 0.0f,
        length, -width,  height, 1.0f, 1.0f,
        length, -width,  height, 1.0f, 1.0f,
        -length, -width,  height, 0.0f, 1.0f,
        -length, -width, -height, 0.0f, 0.0f,

        length,  width,  height, 1.0f, 1.0f,
        length,  width, -height, 1.0f, 0.0f,
        -length,  width, -height, 0.0f, 0.0f,
        -length,  width, -height, 0.0f, 0.0f,
        -length,  width,  height, 0.0f, 1.0f,
        length,  width,  height, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
}
