/**
 * @author Graeme Prendergast
 */

#include "config.h"
#include "triangle_mesh.h"

TriangleMesh::TriangleMesh()
{
    std::vector<float> positions {
        -1.0f, -1.0f,  0.0f,  // bottom left
         1.0f, -1.0f,  0.0f,  // bottom right
        -1.0f,  1.0f,  0.0f,  // top left
         1.0f,  1.0f,  0.0f   // top right
    };

    std::vector<int> elements_to_draw{
        0, 1, 2, 2, 1, 3
    };
    element_count = 6;

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    vertex_buffers.resize(2);

    // position
    glGenBuffers(1, &vertex_buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 
        positions.size() * sizeof(float), 
        positions.data(), 
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // element buffer
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        elements_to_draw.size() * sizeof(int),
        elements_to_draw.data(),
        GL_STATIC_DRAW);
}

TriangleMesh::~TriangleMesh()
{
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(vertex_buffers.size(), vertex_buffers.data());
    glDeleteBuffers(1, &element_buffer);
}

void TriangleMesh::draw()
{
    glBindVertexArray(vertex_array);
    glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
}
