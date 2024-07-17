/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: common functions of vector type
*/

#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include <cmath>
#include <algorithm>

namespace mas {
    /**
    * @brief cast Vector2<SRC> to Vector2<DST>
    */
    template<typename SRC, typename DST>
    inline Vector2<DST> cast_to(const Vector2<SRC> &v) {
        return Vector2<DST>{
            static_cast<DST>(v.x),
            static_cast<DST>(v.y)
        };
    }

    /**
    * @brief cast Vector3<SRC> to Vector3<DST>
    */
    template<typename SRC, typename DST>
    inline Vector3<DST> cast_to(const Vector3<SRC> &v) {
        return Vector3<DST>{
            static_cast<DST>(v.x),
            static_cast<DST>(v.y),
            static_cast<DST>(v.z)
        };
    }

    /**
    * @brief cast Vector4<SRC> to Vector4<DST>
    */
    template<typename SRC, typename DST>
    inline Vector4<DST> cast_to(const Vector4<SRC> &v) {
        return Vector4<DST>{
            static_cast<DST>(v.x),
            static_cast<DST>(v.y),
            static_cast<DST>(v.z),
            static_cast<DST>(v.w)
        };
    }

    /**
     * @brief get the min component of two Vector2<T>
     */
    template<typename T>
    inline Vector2<T> min(const Vector2<T> &v1, const Vector2<T> &v2) {
        Vector2<T> res;
        res.x = std::min(v1.x, v2.x);
        res.y = std::min(v1.y, v2.y);
        return res;
    }

    /**
     * @brief get the min component of two Vector3<T>
     */
    template<typename T>
    inline Vector3<T> min(const Vector3<T> &v1, const Vector3<T> &v2) {
        Vector3<T> res;
        res.x = std::min(v1.x, v2.x);
        res.y = std::min(v1.y, v2.y);
        res.z = std::min(v1.z, v2.z);
        return res;
    }

    /**
     * @brief get the min component of two Vector4<T>
     */
    template<typename T>
    inline Vector4<T> min(const Vector4<T> &v1, const Vector4<T> &v2) {
        Vector4<T> res;
        res.x = std::min(v1.x, v2.x);
        res.y = std::min(v1.y, v2.y);
        res.z = std::min(v1.z, v2.z);
        res.w = std::min(v1.w, v2.w);
        return res;
    }

    /**
     * @brief get the max component of two Vector2<T>
     */
    template<typename T>
    inline Vector2<T> max(const Vector2<T> &v1, const Vector2<T> &v2) {
        Vector2<T> res;
        res.x = std::max(v1.x, v2.x);
        res.y = std::max(v1.y, v2.y);
        return res;
    }

    /**
     * @brief get the max component of two Vector3<T>
     */
    template<typename T>
    inline Vector3<T> max(const Vector3<T> &v1, const Vector3<T> &v2) {
        Vector3<T> res;
        res.x = std::max(v1.x, v2.x);
        res.y = std::max(v1.y, v2.y);
        res.z = std::max(v1.z, v2.z);
        return res;
    }

    /**
     * @brief get the max component of two Vector4<T>
     */
    template<typename T>
    inline Vector4<T> max(const Vector4<T> &v1, const Vector4<T> &v2) {
        Vector4<T> res;
        res.x = std::max(v1.x, v2.x);
        res.y = std::max(v1.y, v2.y);
        res.z = std::max(v1.z, v2.z);
        res.w = std::max(v1.w, v2.w);
        return res;
    }

    /**
     * @brief raise Vector2<T> to the power 'exponent'
     */
    template<typename T>
    inline Vector2<T> pow(const Vector2<T> &base, const Vector2<T> &exponent) {
        return Vector2<T>{
            std::pow(base.x, exponent.x),
            std::pow(base.y, exponent.y)
        };
    }

    /**
     * @brief raise Vector3<T> to the power 'exponent'
     */
    template<typename T>
    inline Vector3<T> pow(const Vector3<T> &base, const Vector3<T> &exponent) {
        return Vector3<T>{
            std::pow(base.x, exponent.x),
            std::pow(base.y, exponent.y),
            std::pow(base.z, exponent.z)
        };
    }

    /**
     * @brief raise Vector4<T> to the power 'exponent'
     */
    template<typename T>
    inline Vector4<T> pow(const Vector4<T> &base, const Vector4<T> &exponent) {
        return Vector4<T>{
            std::pow(base.x, exponent.x),
            std::pow(base.y, exponent.y),
            std::pow(base.z, exponent.z),
            std::pow(base.w, exponent.w)
        };
    }

    /**
     * @brief clamp components of Vector2<T>
     */
    template<typename T>
    inline Vector2<T> clamp(const Vector2<T> &v, const Vector2<T> &min_v, const Vector2<T> &max_v) {
        return Vector2<T>{
            std::clamp(v.x, min_v.x, max_v.x),
            std::clamp(v.y, min_v.y, max_v.y)
        };
    }

    /**
     * @brief clamp components of Vector3<T>
     */
    template<typename T>
    inline Vector3<T> clamp(const Vector3<T> &v, const Vector3<T> &min_v, const Vector3<T> &max_v) {
        return Vector3<T>{
            std::clamp(v.x, min_v.x, max_v.x),
            std::clamp(v.y, min_v.y, max_v.y),
            std::clamp(v.z, min_v.z, max_v.z)
        };
    }

    /**
     * @brief clamp components of Vector4<T>
     */
    template<typename T>
    inline Vector4<T> clamp(const Vector4<T> &v, const Vector4<T> &min_v, const Vector4<T> &max_v) {
        return Vector4<T>{
            std::clamp(v.x, min_v.x, max_v.x),
            std::clamp(v.y, min_v.y, max_v.y),
            std::clamp(v.z, min_v.z, max_v.z),
            std::clamp(v.w, min_v.w, max_v.w)
        };
    }

    /**
    * @brief dot product of Vector2
    */
    template<typename T>
    inline T dot(const Vector2<T> &v1, const Vector2<T> &v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    /**
    * @brief dot product of Vector3
    */
    template<typename T>
    inline T dot(const Vector3<T> &v1, const Vector3<T> &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    /**
    * @brief dot product of Vector4
    */
    template<typename T>
    inline T dot(const Vector4<T> &v1, const Vector4<T> &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    /**
     * @brief cross product of Vector3
     * @return the result of v1 x v2
     */
    template<typename T>
    inline Vector3<T> cross(const Vector3<T> &v1, const Vector3<T> &v2) {
        return Vector3<T>{
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        };
    }

    /**
    * @brief get the length of Vector2
    */
    template<typename T>
    inline double length(const Vector2<T> &v) {
        return std::sqrt(dot(v, v));
    }

    /**
    * @brief get the length of Vector3
    */
    template<typename T>
    inline double length(const Vector3<T> &v) {
        return std::sqrt(dot(v, v));
    }

    /**
    * @brief get the length of Vector4
    */
    template<typename T>
    inline double length(const Vector4<T> &v) {
        return std::sqrt(dot(v, v));
    }

    /**
     * @brief get the distance between two Vector2<T> points
     */
    template<typename T>
    inline double distance(const Vector2<T> &v1, const Vector2<T> &v2) {
        return length(v1 - v2);
    }

    /**
     * @brief get the distance between two Vector3<T> points
     */
    template<typename T>
    inline double distance(const Vector3<T> &v1, const Vector3<T> &v2) {
        return length(v1 - v2);
    }

    /**
     * @brief get the distance between two Vector4<T> points
     */
    template<typename T>
    inline double distance(const Vector4<T> &v1, const Vector4<T> &v2) {
        return length(v1 - v2);
    }

    /**
    * @brief get normalized Vector2
    */
    template<typename T>
    inline Vector2<T> normalize(const Vector2<T> &v) {
        double len = length(v);
        if (len == 0) return v;
        return v / static_cast<T>(len);
    }

    /**
    * @brief get normalized Vector3
    */
    template<typename T>
    inline Vector3<T> normalize(const Vector3<T> &v) {
        double len = length(v);
        if (len == 0) return v;
        return v / static_cast<T>(len);
    }

    /**
    * @brief get normalized Vector4
    */
    template<typename T>
    inline Vector4<T> normalize(const Vector4<T> &v) {
        double len = length(v);
        if (len == 0) return v;
        return v / static_cast<T>(len);
    }
}
