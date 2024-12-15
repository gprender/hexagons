#include "config.h"

class Camera 
{
public:
    Camera(glm::vec3 const position);

    glm::mat4 get_view_transform();

    void move(glm::vec3 const dPos);

    void spin(glm::vec3 const dEulers);
private:
    glm::vec3 position;
    glm::vec3 eulers { 0.0f, 0.0f, 0.0f };
    glm::vec3 const global_up { 0.0f, 0.0f, 1.0f};

    glm::vec3 forwards { 1.0f, 0.0f, 0.0f };
    glm::vec3 right { 0.0f, 1.0f, 0.0f };
    glm::vec3 up { 0.0f, 0.0f, 1.0f };
};