/**
* @author Graeme Prendergast 
*/

#pragma once

#include "../config.h"


class HexagonalTileMesh
{
public:
    HexagonalTileMesh();
    ~HexagonalTileMesh();
    void draw();

private:
    OpenGlId vertex_array;
    OpenGlId vertex_buffer;
    uint32_t vertex_count = 0;

    void make_mesh();
};