/**
 * @author Graeme Prendergast
 */

#include "config.h"
#include "triangle_mesh.h"

TriangleMesh::TriangleMesh()
{
    std::vector<float> data {
        -0.9f,  0.9f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.9f, -0.9f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.9f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    vertex_count = 3;

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // colour
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

    glEnableVertexAttribArray(1);
}

TriangleMesh::~TriangleMesh()
{
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);
}

void TriangleMesh::draw()
{
    glBindVertexArray(vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}
