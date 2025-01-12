/**
* @author Graeme Prendergast 
*/

#include "HexagonalTileMesh.h"

#include "../utilities/ObjReader.h"


HexagonalTileMesh::HexagonalTileMesh()
{
	make_mesh();
}

HexagonalTileMesh::~HexagonalTileMesh()
{
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteVertexArrays(1, &vertex_array);
}

void HexagonalTileMesh::draw()
{
	glBindVertexArray(vertex_array);
	glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void HexagonalTileMesh::make_mesh()
{
	std::vector<float> vertices;
	ObjReader::read_obj_mesh("assets/meshes/hexagonal_tile_tr.obj", vertices);
    vertex_count = vertices.size() / 8;

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)((3 + 2) * sizeof(float)));
    glEnableVertexAttribArray(2);
}
