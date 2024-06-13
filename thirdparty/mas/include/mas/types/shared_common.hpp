/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
* 
* @version: 2.0
* @brief: vector and matrix types' shared functions
*/

#pragma once
#include "vector/common.hpp"
#include "matrix/common.hpp"

namespace mas {
    /**
     * @section Matrix * Vector operator functions
     */

    template<typename T>
    Vector2<T> operator*(Matrix2<T>& m, const Vector2<T>& v) {
        return Vector2<T> {
            m[0][0] * v.x + m[1][0] * v.y,
            m[0][1] * v.x + m[1][1] * v.y
        };
    }

    template <typename T>
    Vector3<T> operator*(Matrix3<T>& m, const Vector3<T>& v) {
        return Vector3<T> {
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z
        };
    }

    template <typename T>
    Vector4<T> operator*(Matrix4<T>& m, const Vector4<T>& v) {
        return Vector4<T> {
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
            m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w
        };
    }
}