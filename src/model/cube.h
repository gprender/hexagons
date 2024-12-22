#include "../config.h"


class Cube 
{
public:
    Cube(glm::vec3 const position);
    void update(float const delta_rotation);
    glm::mat4 get_model_transform(); 

private:
    glm::vec3 position;
    glm::vec3 rotation { 0.0f, 0.0f, 0.0f };
};
