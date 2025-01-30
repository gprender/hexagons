/**
 * @author Graeme Prendergast 
 */

#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"
#include "components/physics_component.h"
#include "components/render_component.h"
#include "components/transform_component.h"

#include "factories/factory.h"


int main()
{
    App app;

    EntityFactory factory(
        app.transform_components, 
        app.physics_components, 
        app.render_components);

    auto hex_ids = factory.make_hexagonal_grid(10, 10);

    EntityId camera_id = factory.make_camera({ 0.0f, -4.0f, 5.0f }, {  0.0f, -90.0f, 90.0f });
    app.camera_component = std::make_shared<CameraComponent>();
    app.camera_id = camera_id;

    app.set_up_opengl();
    app.make_systems();

    app.run();

    return 0;
}

