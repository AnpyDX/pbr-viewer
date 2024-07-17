/** PBRV Project (https://github.com/anpydx/pbr-viewer)
 * @brief first person free-camera object
 */

#pragma once
#define MAS_UTYPE_FLOAT
#include <mas/mas.hpp>

namespace PBRV {
    class Camera {
    public:
        Camera() = delete;
        Camera(mas::vec3 position, mas::vec3 center, mas::vec3 up);

        // get LookAt matrix
        mas::mat4 get_lookat();

        // get camera position
        mas::vec3 get_position();

        // get camera direction
        mas::vec3 get_direction();

        // camera controller
        void position_controller(float front_offset, float right_offset);
        void view_controller(float right_offset, float up_offset);

    private:
        // camera position
        mas::vec3 position {};

        // initial camera coord
        mas::vec3 front {};
        mas::vec3 left {};
        mas::vec3 up {};

        // current camera coord
        mas::vec3 rt_front {};
        mas::vec3 rt_left {};

        // camera view
        float yaw = 0.0f;
        float pitch = 0.0f;
    };
}