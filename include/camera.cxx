#include "Camera.h"
#include <cmath>
#include <algorithm>
#include <imgui/imgui.h>

namespace PBRV {
    Camera::Camera(GLFWwindow* window, mas::vec3 position, mas::vec3 center, mas::vec3 up): window(window) {
        this->position = position;
        this->up = mas::normalize(up);
        this->front = mas::normalize(center - position);
        this->left = mas::normalize(mas::cross(up, front));
        this->rt_front = this->front;
        this->rt_left = this->left;
    }

    mas::mat4 Camera::get_lookat() {
        rt_front = front * std::cos(mas::radians(yaw)) + left * std::sin(mas::radians(yaw)) + up * std::tan(mas::radians(pitch));
        rt_front = mas::normalize(rt_front);
        rt_left = mas::normalize(mas::cross(mas::vec3(0.0, 1.0, 0.0), rt_front));
        mas::vec3 rt_up = mas::normalize(mas::cross(rt_front, rt_left));

        mas::mat4 result = mas::lookAt(position, position + rt_front, rt_up);
        return result;
    }

    mas::mat4 Camera::get_perspective() {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        return mas::perspective(fov, static_cast<float>(width) / static_cast<float>(height), near_plane, far_plane);
    }

    mas::vec3 Camera::get_position() {
        return position;
    }

    mas::vec3 Camera::get_direction() {
        return rt_front;
    }

    void Camera::update_input(float delta_time) {
        mas::vec2 camera_movement(0.0f);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera_movement.y += 1.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera_movement.y -= 1.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera_movement.x -= 1.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera_movement.x += 1.0f;
        }

        camera_movement = mas::normalize(camera_movement) * speed * delta_time;
        this->position_controller(camera_movement.y, camera_movement.x);
        
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (ImGui::IsAnyItemHovered() || ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused()) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            
                double mouse_x, mouse_y;
                glfwGetCursorPos(window, &mouse_x, &mouse_y);
                auto xpos = static_cast<float>(mouse_x);
                auto ypos = static_cast<float>(mouse_y);

                if (!mouse_released) {
                    mas::vec2 view_offset(xpos - last_mouse_pos.x, last_mouse_pos.y - ypos);
                    view_offset = view_offset * sensitivity * delta_time;
                    this->view_controller(view_offset.x, view_offset.y);
                }
                else {
                    mouse_released = false;
                }

                last_mouse_pos.x = xpos;
                last_mouse_pos.y = ypos;
            }
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            mouse_released = true;
        }
        
    }

    void Camera::position_controller(float front_offset, float right_offset) {
        position = position + rt_front * front_offset;
        position = position - rt_left * right_offset;
    }

    void Camera::view_controller(float right_offset, float up_offset) {
        yaw -= right_offset;
        pitch += up_offset;

        pitch = std::clamp(pitch, -89.5f, 89.5f);
    }
}