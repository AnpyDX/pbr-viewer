/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: common functions of matrix type
*/

#pragma once
#include "Matrix2.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"

namespace mas {
    /**
     * @brief transpose Matrix2<T>
     */
    template<typename T>
    Matrix2<T> transpose(const Matrix2<T> &value) {
         return Matrix2<T> {
             value[0][0], value[0][1],
             value[1][0], value[1][1]
         };
    }

    /**
     * @brief transpose Matrix3<T>
     */
    template<typename T>
    Matrix3<T> transpose(const Matrix3<T> &value) {
        return Matrix3<T> {
            value[0][0], value[0][1], value[0][2],
            value[1][0], value[1][1], value[1][2],
            value[2][0], value[2][1], value[2][2]
        };
    }

    /**
     * @brief transpose Matrix4<T>
     */
    template<typename T>
    Matrix4<T> transpose(const Matrix4<T> &value) {
        return Matrix4<T> {
            value[0][0], value[0][1], value[0][2], value[0][3],
            value[1][0], value[1][1], value[1][2], value[1][3],
            value[2][0], value[2][1], value[2][2], value[2][3],
            value[3][0], value[3][1], value[3][2], value[3][3]
        };
    }
}
