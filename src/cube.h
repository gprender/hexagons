#include "config.h"

class Cube 
{
public:
    Cube(glm::vec3 const position, glm::vec3 const size);

    ~Cube();

    void update(float const dt);
    void draw(OpenGlId const shader);

private:
    glm::vec3 position;
    glm::vec3 eulers;

    OpenGlId vertex_array;
    OpenGlId vertex_buffer;
    OpenGlId texture;

    void make_texture();
    void make_mesh(float const l, float const w, float const h);
};
