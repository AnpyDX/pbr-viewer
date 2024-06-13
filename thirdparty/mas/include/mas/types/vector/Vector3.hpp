/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: type defination of Vector3D
*/

#pragma once
#include "Vector2.hpp"

namespace mas {
    template<typename T>
    class Vector3 {
    public:
        Vector3()
            : x(0), y(0), z(0) {
        }

        explicit Vector3(const T &scalar)
            : x(scalar), y(scalar), z(scalar) {
        }

        Vector3(const Vector2<T> &v, const T &z)
            : x(v.x), y(v.y), z(z) {
        }

        Vector3(const T &x, const T &y, const T &z)
            : x(x), y(y), z(z) {
        }

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
    };

    template<typename T>
    inline Vector3<T> operator-(const Vector3<T> &v) {
        return Vector3<T>{-v.x, -v.y, -v.z};
    }

    template<typename T>
    inline Vector3<T> operator+(const Vector3<T> &v1, const Vector3<T> &v2) {
        return Vector3<T>{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    }

    template<typename T>
    inline Vector3<T> operator-(const Vector3<T> &v1, const Vector3<T> &v2) {
        return Vector3<T>{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    }

    template<typename T>
    inline Vector3<T> operator*(const Vector3<T> &v1, const Vector3<T> &v2) {
        return Vector3<T>{v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
    }

    template<typename T>
    inline Vector3<T> operator/(const Vector3<T> &v1, const Vector3<T> &v2) {
        return Vector3<T>{v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
    }

    template<typename T, typename U>
    inline Vector3<T> operator+(const Vector3<T> &v, const U &n) {
        return Vector3<T>{v.x + n, v.y + n, v.z + n};
    }

    template<typename T, typename U>
    inline Vector3<U> operator+(const T &n, const Vector3<U> &v) {
        return v + n;
    }

    template<typename T, typename U>
    inline Vector3<T> operator-(const Vector3<T> &v, const U &n) {
        return Vector3<T>{v.x - n, v.y - n, v.z - n};
    }

    template<typename T, typename U>
    inline Vector3<U> operator-(const T &n, const Vector3<U> &v) {
        return Vector3<U>{n - v.x, n - v.y, n - v.z};
    }

    template<typename T, typename U>
    inline Vector3<T> operator*(const Vector3<T> &v, const U &n) {
        return Vector3<T>{v.x * n, v.y * n, v.z * n};
    }

    template<typename T, typename U>
    inline Vector3<U> operator*(const T &n, const Vector3<U> &v) {
        return v * n;
    }

    template<typename T, typename U>
    inline Vector3<T> operator/(const Vector3<T> &v, const U &n) {
        return Vector3<T>{v.x / n, v.y / n, v.z / n};
    }

    template<typename T, typename U>
    inline Vector3<U> operator/(const T &n, const Vector3<U> &v) {
        return Vector3<U>{n / v.x, n / v.y, n / v.z};
    }
}
