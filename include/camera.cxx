#include "camera.h"
#include <cmath>

namespace PBRV {
    Camera::Camera(mas::vec3 position, mas::vec3 center, mas::vec3 up) {
        this->position = position;
        this->up = mas::normalize(up);
        this->front = mas::normalize(center - position);
        this->left = mas::normalize(mas::cross(this->up, front));
    }

    mas::mat4 Camera::get_lookat() {
        direction = front * std::cos(mas::radians(yaw)) + left * std::sin(mas::radians(yaw)) + up * std::tan(mas::radians(pitch));
        direction = mas::normalize(direction);
        mas::vec3 cam_left = mas::normalize(mas::cross(mas::vec3(0.0, 1.0, 0.0), direction));
        mas::vec3 cam_up = mas::normalize(mas::cross(direction, cam_left));
        
        mas::mat4 result = mas::lookAt(position, position + direction, cam_up);
        return result;
    }

    void Camera::position_controller(float front_offset, float right_offset) {
        position = position + this->front * front_offset;
        position = position - this->left * right_offset;
    }

    void Camera::view_controller(float right_offset, float up_offset) {
        yaw -= right_offset;
        pitch += up_offset;
    }
}