/**
 * PBR-Viewer
 * >> Camera Object
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

        // camera controller
        void position_controller(float front_offset, float right_offset);
        void view_controller(float right_offset, float up_offset);

    public:
        mas::vec3 position {};
        mas::vec3 direction {};

    private:
        // initial camera coord
        mas::vec3 front {};
        mas::vec3 left {};
        mas::vec3 up {};

        // camera view
        float yaw = 0.0f;
        float pitch = 0.0f;
    };
}