/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: type defination of Matrix 2x2
*/

#pragma once

namespace mas {
    template<typename T>
    class Matrix2 {
    public:
        Matrix2() {
            value[0][0] = 0;
            value[0][1] = 0;
            value[1][0] = 0;
            value[0][1] = 0;
        }

        Matrix2(const Matrix2<T> &m) {
            value[0][0] = m.value[0][0];
            value[0][1] = m.value[0][1];
            value[1][0] = m.value[1][0];
            value[0][1] = m.value[1][1];
        }

        Matrix2(
            const T &x0, const T &y0,
            const T &x1, const T &y1) {
            value[0][0] = x0;
            value[0][1] = x1;
            value[1][0] = y0;
            value[1][1] = y1;
        }

        explicit Matrix2(const T &scalar) {
            value[0][0] = scalar;
            value[1][1] = scalar;
            value[0][1] = 0;
            value[1][0] = 0;
        }

        T *operator[](const int &index) {
            return value[index];
        }

    private:
        /**
         * Matrix 2x2
         * Memory Layout
         *  [0]  [1]
         *  x0   y0
         *  x1   y1
         */
        T value[2][2];
    };

    template<typename T>
    inline Matrix2<T> operator+(Matrix2<T> &m1, Matrix2<T> &m2) {
        return Matrix2<T>{
            m1[0][0] + m2[0][0],
            m1[1][0] + m2[1][0],
            m1[0][1] + m2[0][1],
            m1[1][1] + m2[1][1]
        };
    }

    template<typename T>
    inline Matrix2<T> operator-(Matrix2<T> &m1, Matrix2<T> &m2) {
        return Matrix2<T>{
            m1[0][0] - m2[0][0],
            m1[1][0] - m2[1][0],
            m1[0][1] - m2[0][1],
            m1[1][1] - m2[1][1]
        };
    }

    template<typename T>
    inline Matrix2<T> operator*(Matrix2<T> &m1, Matrix2<T> &m2) {
        return Matrix2<T>{
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]
        };
    }

    template<typename T, typename U>
    inline Matrix2<T> operator+(Matrix2<T> &m, U &n) {
        return Matrix2<T>{
            m[0][0] + n,
            m[1][0] + n,
            m[0][1] + n,
            m[1][1] + n
        };
    }

    template<typename T>
    inline Matrix2<T> operator+(T &n, Matrix2<T> &m) {
        return m + n;
    }

    template<typename T>
    inline Matrix2<T> operator-(Matrix2<T> &m, T &n) {
        return Matrix2<T>{
            m[0][0] - n,
            m[1][0] - n,
            m[0][1] - n,
            m[1][1] - n
        };
    }

    template<typename T>
    inline Matrix2<T> operator-(T &n, Matrix2<T> &m) {
        return Matrix2<T>{
            n - m[0][0],
            n - m[1][0],
            n - m[0][1],
            n - m[1][1]
        };
    }

    template<typename T>
    inline Matrix2<T> operator*(Matrix2<T> &m, T &n) {
        return Matrix2<T>{
            m[0][0] * n,
            m[1][0] * n,
            m[0][1] * n,
            m[1][1] * n
        };
    }

    template<typename T>
    inline Matrix2<T> operator*(T &n, Matrix2<T> &m) {
        return m * n;
    }

    template<typename T>
    inline Matrix2<T> operator/(Matrix2<T> &m, T &n) {
        return Matrix2<T>{
            m[0][0] / n,
            m[1][0] / n,
            m[0][1] / n,
            m[1][1] / n
        };
    }

    template<typename T>
    inline Matrix2<T> operator/(T &n, Matrix2<T> &m) {
        return Matrix2<T>{
            n / m[0][0],
            n / m[1][0],
            n / m[0][1],
            n / m[1][1]
        };
    }
}
