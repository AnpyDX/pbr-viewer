/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: types memory pointer utility
*/

#pragma once
#include "../types/shared_common.hpp"

namespace mas {
    /**
     * @brief get Vector2<T> data's pointer
     */
    template <typename T>
    T* get_value_ptr(Vector2<T>& type_obj) {
        return reinterpret_cast<T*>(&type_obj);
    }

    /**
     * @brief get Vector3<T> data's pointer
     */
    template <typename T>
    T* get_value_ptr(Vector3<T>& type_obj) {
        return reinterpret_cast<T*>(&type_obj);
    }

    /**
     * @brief get Vector4<T> data's pointer
     */
    template <typename T>
    T* get_value_ptr(Vector4<T>& type_obj) {
        return reinterpret_cast<T*>(&type_obj);
    }

    /**
     * @brief get Matrix2<T> data's pointer
     */
    template <typename T>
    T* get_value_ptr(Matrix2<T>& type_obj) {
        return type_obj[0];
    }

    /**
     * @brief get Matrix3<T> data's pointer
     */
    template <typename T>
    T* get_value_ptr(Matrix3<T>& type_obj) {
        return type_obj[0];
    }

    /**
     * @brief get Matrix4<T> data's pointer
     */
    template <typename T>
    T* get_value_ptr(Matrix4<T>& type_obj) {
        return type_obj[0];
    }
}