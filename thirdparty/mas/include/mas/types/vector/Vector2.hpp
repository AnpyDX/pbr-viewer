/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: type defination of Vector2D
*/

#pragma once

namespace mas {
    template<typename T>
    class Vector2 {
    public:
        Vector2()
            : x(0), y(0) {
        }

        explicit Vector2(const T &scalar)
            : x(scalar), y(scalar) {
        }

        Vector2(const T &x, const T &y)
            : x(x), y(y) {
        }

    public:
        union {
            T x;
            T u;
        };

        union {
            T y;
            T v;
        };
    };

    template<typename T>
    inline Vector2<T> operator-(const Vector2<T> &v) {
        return Vector2<T>{-v.x, -v.y};
    }

    template<typename T>
    inline Vector2<T> operator+(const Vector2<T> &v1, const Vector2<T> &v2) {
        return Vector2<T>{v1.x + v2.x, v1.y + v2.y};
    }

    template<typename T>
    inline Vector2<T> operator-(const Vector2<T> &v1, const Vector2<T> &v2) {
        return Vector2<T>{v1.x - v2.x, v1.y - v2.y};
    }

    template<typename T>
    inline Vector2<T> operator*(const Vector2<T> &v1, const Vector2<T> &v2) {
        return Vector2<T>{v1.x * v2.x, v1.y * v2.y};
    }

    template<typename T>
    inline Vector2<T> operator/(const Vector2<T> &v1, const Vector2<T> &v2) {
        return Vector2<T>{v1.x / v2.x, v1.y / v2.y};
    }

    template<typename T, typename U>
    inline Vector2<T> operator+(const Vector2<T> &v, const U &n) {
        return Vector2<T>{v.x + n, v.y + n};
    }

    template<typename T, typename U>
    inline Vector2<U> operator+(const T &n, const Vector2<U> &v) {
        return v + n;
    }

    template<typename T, typename U>
    inline Vector2<T> operator-(const Vector2<T> &v, const U &n) {
        return Vector2<T>{v.x - n, v.y - n};
    }

    template<typename T, typename U>
    inline Vector2<U> operator-(const T &n, const Vector2<U> &v) {
        return Vector2<U>{n - v.x, n - v.y};
    }

    template<typename T, typename U>
    inline Vector2<T> operator*(const Vector2<T> &v, const U &n) {
        return Vector2<T>{v.x * n, v.y * n};
    }

    template<typename T, typename U>
    inline Vector2<U> operator*(const T &n, const Vector2<U> &v) {
        return v * n;
    }

    template<typename T, typename U>
    inline Vector2<T> operator/(const Vector2<T> &v, const U &n) {
        return Vector2<T>{v.x / n, v.y / n};
    };

    template<typename T, typename U>
    inline Vector2<U> operator/(const T &n, const Vector2<U> &v) {
        return Vector2<U>{n / v.x, n / v.y};
    };
}
