/**
* @author Graeme Prendergast 
*/

#pragma once

#include "../config.h"

namespace ObjReader
{
    void read_obj_mesh(
        std::string const& filename, 
        std::vector<float>& vertices,
        glm::mat4 const pretransform
    );

    void reserve_obj_mesh_vectors(
        std::string const& filename,
        std::vector<glm::vec3>& v,  /* out */
        std::vector<glm::vec2>& vt, /* out */
        std::vector<glm::vec3>& vn, /* out */
        std::vector<float>& f       /* out */
    );

    void fill_obj_mesh_vectors(
        std::string const& filename,
        std::vector<glm::vec3>& v,  /* out */
        std::vector<glm::vec2>& vt, /* out */
        std::vector<glm::vec3>& vn, /* out */
        glm::mat4 const pretransform
    );

    void fill_vertex_vector(std::string const& filename,
        std::vector<glm::vec3>& v,  /* out */
        std::vector<glm::vec2>& vt, /* out */
        std::vector<glm::vec3>& vn, std::vector<float>& vertices       /* out */
    );

    void parse_vertex_description(
        std::string const& vertex_description,
        std::vector<glm::vec3>& v,  /* out */
        std::vector<glm::vec2>& vt, /* out */
        std::vector<glm::vec3>& vn, /* out */
        std::vector<float>& f       /* out */
    );

    glm::vec2 to_vec2(std::vector<std::string>::iterator it);

    glm::vec3 to_vec3(std::vector<std::string>::iterator it);
}
