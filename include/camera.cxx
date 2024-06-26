#include "camera.h"
#include <cmath>

namespace PBRV {
    Camera::Camera(mas::vec3 position, mas::vec3 center, mas::vec3 up) {
        this->position = position;
        this->up = mas::normalize(up);
        this->front = mas::normalize(center - position);
        this->left = mas::normalize(mas::cross(this->up, front));
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

    mas::vec3 Camera::get_position() {
        return position;
    }

    mas::vec3 Camera::get_direction() {
        return rt_front;
    }

    void Camera::position_controller(float front_offset, float right_offset) {
        position = position + rt_front * front_offset;
        position = position - rt_left * right_offset;
    }

    void Camera::view_controller(float right_offset, float up_offset) {
        yaw -= right_offset;
        pitch += up_offset;
    }
}