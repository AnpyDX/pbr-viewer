/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: transform matrix generator utils
*/

#pragma once
#include "../types/shared_common.hpp"

namespace mas {
    /**
     * @brief generate a translate matrix
     * @param m previous matrix
     * @param v movement factor
     * @return Matrix4<T>
     */
    template <typename T>
    inline Matrix4<T> translate(Matrix4<T> m, const Vector3<T>& v) {
        m[3][0] += v.x;
        m[3][1] += v.y;
        m[3][2] += v.z;
        return m;
    }

    /**
     * @brief generate a rotate matrix
     * @param m previous matrix
     * @param v rotation axis
     * @param angle rotate angle
     * @return Matrix4<T>
     */
    template <typename T>
    inline Matrix4<T> rotate(Matrix4<T> m, const Vector3<T>& v, double angle) {
        T sin_a = static_cast<T>(std::sin(angle));
        T cos_a = static_cast<T>(std::cos(angle));
        Vector3<T> axis = normalize(v);
        Vector3<T> temp = (static_cast<T>(1) - cos_a) * axis;

        Matrix4<T> result(1.0);
        result[0][0] = cos_a + temp.x * axis.x;
        result[0][1] = temp.x * axis.y + sin_a * axis.z;
        result[0][2] = temp.x * axis.z - sin_a * axis.y;

        result[1][0] = temp.y * axis.x - sin_a * axis.z;
        result[1][1] = cos_a + temp.y * axis.y;
        result[1][2] = temp.y * axis.z + sin_a * axis.x;

        result[2][0] = temp.z * axis.x + sin_a * axis.y;
        result[2][1] = temp.z * axis.y - sin_a * axis.x;
        result[2][2] = cos_a + temp.z * axis.z;

        return m * result;
    }

    /**
     * @brief generate a scaling matrix
     * @param m previous matrix
     * @param v scaling factor
     * @return Matrix4<T>
     */
    template <typename T>
    inline Matrix4<T> scale(Matrix4<T> m, const Vector3<T>& v) {
        m[0][0] *= v.x;
        m[1][1] *= v.y;
        m[2][2] *= v.z;
        return m;
    }
}