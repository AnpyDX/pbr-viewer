/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: lookAt matrix generator utils
*/

#pragma once
#include "../types/shared_common.hpp"

namespace mas {

    /**
     * @brief generate a lookat matrix
     * @param pos position of camera
     * @param center position where camera looking at
     * @param up camera up direction
     * @return Matrix4<T> generated lookAt martix
     */
    template <typename T>
    inline Matrix4<T> lookAt(const Vector3<T>& pos, const Vector3<T>& center, const Vector3<T>& up) {
        Vector3<T> dir = normalize(pos - center);
        Vector3<T> right = normalize(cross(up, dir));
        Matrix4<T> result {
            right.x, right.y, right.z, 0,
            up.x,    up.y,    up.z,    0,
            dir.x,   dir.y,   dir.z,   0,
            0, 0, 0, 1
        };
        result[3][0] = -right.x * pos.x - right.y * pos.y - right.z * pos.z;
        result[3][1] = -up.x * pos.x - up.y * pos.y - up.z * pos.z;
        result[3][2] = -dir.x * pos.x - dir.y * pos.y - dir.z * pos.z;

        return result;
    }
}