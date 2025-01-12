/**
* @author Graeme Prendergast 
*/

#include "PolygonMesh.h"

#include "../utilities/ObjReader.h"


PolygonMesh::PolygonMesh(std::string const& obj_filename)
{
	make_mesh(obj_filename);
}

PolygonMesh::PolygonMesh(std::vector<float>& vertices)
{
	make_mesh(vertices);
}

PolygonMesh::~PolygonMesh()
{
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteVertexArrays(1, &vertex_array);
}

void PolygonMesh::draw()
{
	glBindVertexArray(vertex_array);
	glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void PolygonMesh::make_mesh(std::string const& obj_filename)
{
	std::vector<float> vertices;
	ObjReader::read_obj_mesh(obj_filename, vertices);
	make_mesh(vertices);
}

void PolygonMesh::make_mesh(std::vector<float>& vertices)
{
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
