/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: projection matrix generator utils
*/

#pragma once
#include "../types/shared_common.hpp"

#include <cmath>

namespace mas {
    /**
     * @brief generate a perspective projection matrix
     * @param fov fov of view
     * @param aspect aspect of viewport (width / height)
     * @param near near plane
     * @param far far plane
     * @return Matrix4<T> generated perspective martix
     */
    template <typename T>
    inline Matrix4<T> perspective(T fov, T aspect, T near, T far) {
        float tanHalFov = tan(fov/ static_cast<T>(2));
        Matrix4<T> res(0.0);
        res[0][0] = static_cast<T>(1) / (aspect * tanHalFov);
        res[1][1] = static_cast<T>(1) / tanHalFov;
        res[2][2] = (far + near) / (near - far);
        res[2][3] = -static_cast<T>(1);
        res[3][2] = static_cast<T>(2) * near * far / (near - far);

        return res;
    }

    /**
     * @brief generate a ortho projection matrix
     * @return Matrix4<T> generated ortho martix
     */
    template <typename T>
    inline Matrix4<T> ortho(T left, T right, T bottom, T top, T near, T far) {
        Matrix4<T> res(1.0);
        res[0][0] = static_cast<T>(2) / (right - left);
        res[1][1] = static_cast<T>(2) / (top - bottom);
        res[2][2] = - static_cast<T>(2) / (far - near);
        res[3][0] = - (right + left) / (right - left);
        res[3][1] = - (top + bottom) / (top - bottom);
        res[3][2] = - (far + near) / (far - near);

        return res;
    }
}