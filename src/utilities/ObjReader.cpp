/**
* @author Graeme Prendergast 
*/

#include "ObjReader.h"
#include "StringOps.h"

namespace ObjReader
{
    void read_obj_mesh(std::string const& filename, std::vector<float>& vertices)
    {
        std::vector<glm::vec3> v;
        std::vector<glm::vec2> vt;
        std::vector<glm::vec3> vn;

        reserve_obj_mesh_vectors(filename, v, vt, vn, vertices);

        fill_obj_mesh_vectors(filename, v, vt, vn);

        fill_vertex_vector(filename, v, vt, vn, vertices);
    }

    void reserve_obj_mesh_vectors(
        std::string const& filename,
        std::vector<glm::vec3>& v,  /* out */
        std::vector<glm::vec2>& vt, /* out */
        std::vector<glm::vec3>& vn, /* out */
        std::vector<float>& f       /* out */
    ) {
        size_t vertex_count = 0;
        size_t texture_coord_count = 0;
        size_t normal_count = 0;
        size_t face_count = 0;

        std::ifstream file;
        std::string line;

        file.open(filename);
        while (std::getline(file, line))
        {
            std::vector<std::string> tokens = split(line, " ");

            if (tokens[0].compare("v") == 0)
            {
                ++vertex_count;
            }
            else if (tokens[0].compare("vt") == 0)
            {
                ++texture_coord_count;
            }
            else if (tokens[0].compare("vn") == 0)
            {
                ++normal_count;
            }
            else if (tokens[0].compare("f") == 0)
            {
                face_count += tokens.size() - 3;
            }
        }
        file.close();

        v.reserve(vertex_count);
        vt.reserve(texture_coord_count);
        vn.reserve(normal_count);
        f.reserve(face_count * 3 * (3 + 2 + 3));
    }

    void fill_obj_mesh_vectors(
        std::string const& filename,
        std::vector<glm::vec3>& v,  /* out */
        std::vector<glm::vec2>& vt, /* out */
        std::vector<glm::vec3>& vn  /* out */
    ) {
        std::ifstream file;
        std::string line;

        file.open(filename);
        while (std::getline(file, line))
        {
            std::vector<std::string> tokens = split(line, " ");

            if (tokens[0].compare("v") == 0)
            {
                v.push_back(to_vec3(tokens.begin() + 1));
            }
            else if (tokens[0].compare("vt") == 0)
            {
                vt.push_back(to_vec2(tokens.begin() + 1));
            }
            else if (tokens[0].compare("vn") == 0)
            {
                vn.push_back(to_vec3(tokens.begin() + 1));
            }
        }
        file.close();
    }

    /**
    * Only handles triangulated .obj files
    */
    void fill_vertex_vector(std::string const& filename,
        std::vector<glm::vec3>& v,  /* out */
        std::vector<glm::vec2>& vt, /* out */
        std::vector<glm::vec3>& vn, std::vector<float>& vertices       /* out */
    ) {
        std::ifstream file;
        std::string line;

        file.open(filename);
        while (std::getline(file, line))
        {
            std::vector<std::string> tokens = split(line, " ");

            if (tokens[0].compare("f") == 0)
            {
                parse_vertex_description(tokens[1], v, vt, vn, vertices);
                parse_vertex_description(tokens[2], v, vt, vn, vertices);
                parse_vertex_description(tokens[3], v, vt, vn, vertices);
            }
        }
        file.close();
    }

    void parse_vertex_description(
        std::string const& vertex_description,
        std::vector<glm::vec3>& v,  /* out */
        std::vector<glm::vec2>& vt, /* out */
        std::vector<glm::vec3>& vn, /* out */
        std::vector<float>& f       /* out */
    ) {
        auto const vertex_description_vec = split(vertex_description, "/");

        auto vertex_idx = std::stoi(vertex_description_vec[0]) - 1;
        auto vertex = v[vertex_idx];
        f.push_back(vertex.x);
        f.push_back(vertex.y);
        f.push_back(vertex.z);

        auto vtc_idx = std::stoi(vertex_description_vec[1]) - 1;
        auto texture_coordinates = vt[vtc_idx];
        f.push_back(texture_coordinates[0]);
        f.push_back(texture_coordinates[1]);

        auto normal_idx = std::stoi(vertex_description_vec[2]) - 1;
        auto vertex_normal = vn[normal_idx];
        f.push_back(vertex_normal.x);
        f.push_back(vertex_normal.y);
        f.push_back(vertex_normal.z);
    }

    glm::vec2 to_vec2(std::vector<std::string>::iterator it)
    {
        return glm::vec2(
            std::stof(*it++), 
            std::stof(*it)
        );
    }


    glm::vec3 to_vec3(std::vector<std::string>::iterator it)
    {
        return glm::vec3(
            std::stof(*it++), 
            std::stof(*it++), 
            std::stof(*it)
        );
    }
}
