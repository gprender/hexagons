/**
* @author Graeme Prendergast 
*/

#pragma once

#include "../config.h"


class PolygonMesh
{
public:
    explicit PolygonMesh(std::string const& obj_filename, glm::mat4 const pretransform);
    explicit PolygonMesh(std::vector<float>& vertices);
    ~PolygonMesh();
    void draw();

private:
    OpenGlId vertex_array;
    OpenGlId vertex_buffer;
    uint32_t vertex_count = 0;

    void make_mesh(std::string const& obj_filename, glm::mat4 const pretransform);
    void make_mesh(std::vector<float>& vertices);
};