/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: type defination of Vector4D
*/

#pragma once
#include "Vector3.hpp"

namespace mas {

    template <typename T>
    class Vector4 {
    public:
        Vector4()
        :x(0), y(0), z(0), w(0) {}

        explicit Vector4(const T& scalar)
        : x(scalar), y(scalar), z(scalar), w(scalar) {}

        Vector4(const Vector2<T>& v, const T& z, const T& w)
        : x(v.x), y(v.y), z(z), w(w) {}

        Vector4(const Vector3<T>& v, const T& w)
        : x(v.x), y(v.y), z(v.z), w(w) {}

        Vector4(const T& x, const T& y, const T& z, const T& w)
        : x(x), y(y), z(z), w(w) {}

    public:
        union {
            T x;
            T r;
        };
        union {
            T y;
            T g;
        };
        union {
            T z;
            T b;
        };
        union {
            T w;
            T a;
        };
    };

    template <typename T>
    inline Vector4<T> operator-(const Vector4<T>& v) {
        return Vector4<T> { -v.x, -v.y, -v.z, -v.w };
    }

    template <typename T>
    inline Vector4<T> operator+(const Vector4<T>& v1, const Vector4<T>& v2) {
        return Vector4<T> { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
    }

    template <typename T>
    inline Vector4<T> operator-(const Vector4<T>& v1, const Vector4<T>& v2) {
        return Vector4<T> { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
    }

    template <typename T>
    inline Vector4<T> operator*(const Vector4<T>& v1, const Vector4<T>& v2) {
        return Vector4<T> { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w };
    }

    template <typename T>
    inline Vector4<T> operator/(const Vector4<T>& v1, const Vector4<T>& v2) {
        return Vector4<T> { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w };
    }

    template <typename T, typename U>
    inline Vector4<T> operator+(const Vector4<T>& v, const U& n) {
        return Vector4<T> { v.x + n, v.y + n, v.z + n, v.w + n };
    }

    template <typename T, typename U>
    inline Vector4<U> operator+(const T& n, const Vector4<U>& v) {
        return v + n;
    }

    template <typename T, typename U>
    inline Vector4<T> operator-(const Vector4<T>& v, const U& n) {
        return Vector4<T> { v.x - n, v.y - n, v.z - n, v.w - n };
    }

    template <typename T, typename U>
    inline Vector4<U> operator-(const T& n, const Vector4<U>& v) {
        return Vector4<U> { n - v.x, n - v.y, n - v.z, n - v.w };
    }

    template <typename T, typename U>
    inline Vector4<T> operator*(const Vector4<T>& v, const U& n) {
        return Vector4<T> { v.x * n, v.y * n, v.z * n, v.w * n };
    }

    template <typename T, typename U>
    inline Vector4<U> operator*(const T& n, const Vector4<U>& v) {
        return v * n;
    }

    template <typename T, typename U>
    inline Vector4<T> operator/(const Vector4<T>& v, const U& n) {
        return Vector4<T> { v.x / n, v.y / n, v.z / n, v.w / n };
    }

    template <typename T, typename U>
    inline Vector4<U> operator/(const T& n, const Vector4<U>& v) {
        return Vector4<U> { n / v.x, n / v.y, n / v.z, n / v.w };
    }

}