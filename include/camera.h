/** PBRV Project (https://github.com/anpydx/pbr-viewer)
 * @brief first person free-camera object
 */

#pragma once
#define MAS_UTYPE_FLOAT
#include <mas/mas.hpp>
#include <GLFW/glfw3.h>

namespace PBRV {
    class Camera {
    public:
        Camera() = delete;
        Camera(GLFWwindow* window, mas::vec3 position, mas::vec3 center, mas::vec3 up);

        // get LookAt matrix
        [[nodiscard]]
        mas::mat4 get_lookat();

        // get Prespective matrix
        [[nodiscard]]
        mas::mat4 get_perspective();

        // get camera position
        [[nodiscard]]
        mas::vec3 get_position();

        // get camera direction
        [[nodiscard]]
        mas::vec3 get_direction();

        // update camera controller
        void update_input(float delta_time);

        // set camera position offset manually (recommand to use <update_input> instead)
        void position_controller(float front_offset, float right_offset);
        // set camera view offset manually (recommand to use <update_input> instead)
        void view_controller(float right_offset, float up_offset);

    private:
        // window handle
        GLFWwindow* window;

        // camera position
        mas::vec3 position {};

        // initial camera coord
        mas::vec3 front {};
        mas::vec3 left {};
        mas::vec3 up {};

        // realtime camera coord
        mas::vec3 rt_front {};
        mas::vec3 rt_left {};

        // camera view
        float yaw = 0.0f;
        float pitch = 0.0f;

        // camera controller utils
        bool mouse_released = true;
        mas::vec2 last_mouse_pos { 0.0f };

    public:
        float speed = 0.5f; // camera movement speed
        float sensitivity = 15.0f; // camera view sensitivity

        float fov = 45.0f;
        float near_plane = 0.001f;
        float far_plane = 1000.0f;
    };
}