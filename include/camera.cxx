#include "camera.h"

namespace PBRV {
    Camera::Camera(mas::vec3 position, mas::vec3 center, mas::vec3 up) {
        this->position = position;
        this->up = mas::normalize(up);
        this->front = mas::normalize(center - position);
        this->left = mas::normalize(mas::cross(this->up, front));
    }

    mas::mat4 Camera::get_lookat() {
        mas::mat4 result {};
        result = mas::lookAt(position, position + front, up);
        return result;
    }

    void Camera::position_controller(float front_offset, float right_offset) {
        position = position + this->front * front_offset;
        position = position - this->left * right_offset;
    }

    void Camera::view_controller(float right_offset, float up_offset) {
        mas::vec4 direction(front, 0.0);
        mas::mat4 rotation_mat(1.0);
        rotation_mat = mas::rotate(rotation_mat, up, -right_offset);
        direction = rotation_mat * direction;
        front.x = direction.x;
        front.y = direction.y;
        front.z = direction.z;

        left = mas::normalize(mas::cross(up, front));
        
        rotation_mat = mas::mat4(1.0);
        rotation_mat = mas::rotate(rotation_mat, left, -up_offset);
        direction = mas::vec4(front, 0.0);
        direction = rotation_mat * direction;
        front.x = direction.x;
        front.y = direction.y;
        front.z = direction.z;

        up = mas::normalize(mas::cross(front, left));
    }


}