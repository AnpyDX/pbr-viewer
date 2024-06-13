/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: type defination of Matrix 3x3
*/

#pragma once

namespace mas {
    template<typename T>
    class Matrix3 {
    public:
        Matrix3() {
            for (auto &i: value) {
                i[0] = 0;
                i[1] = 0;
                i[2] = 0;
            }
        }

        Matrix3(const Matrix3<T> &m) {
            for (int i = 0; i < 3; i++) {
                value[i][0] = m.value[i][0];
                value[i][1] = m.value[i][1];
                value[i][2] = m.value[i][2];
            }
        }

        Matrix3(
            const T &x0, const T &y0, const T &z0,
            const T &x1, const T &y1, const T &z1,
            const T &x2, const T &y2, const T &z2) {
            value[0][0] = x0;
            value[0][1] = x1;
            value[0][2] = x2;
            value[1][0] = y0;
            value[1][1] = y1;
            value[1][2] = y2;
            value[2][0] = z0;
            value[2][1] = z1;
            value[2][2] = z2;
        }

        explicit Matrix3(const T &scalar) {
            value[0][0] = scalar;
            value[0][1] = 0;
            value[0][2] = 0;
            value[1][0] = 0;
            value[1][1] = scalar;
            value[1][2] = 0;
            value[2][0] = 0;
            value[2][1] = 0;
            value[2][2] = scalar;
        }

        T *operator[](const int &index) {
            return value[index];
        }

    private:
        /**
         * Matrix 3x3
         * Memory Layout
         *  [0]  [1]  [2]
         *  x0   y0   z0
         *  x1   y1   z1
         *  x2   y2   z2
         */
        T value[3][3];
    };

    template<typename T>
    inline Matrix3<T> operator+(Matrix3<T> &m1, Matrix3<T> &m2) {
        return Matrix3<T>{
            m1[0][0] + m2[0][0], m1[1][0] + m2[1][0], m1[2][0] + m2[2][0],
            m1[0][1] + m2[0][1], m1[1][1] + m2[1][1], m1[2][1] + m2[2][1],
            m1[0][2] + m2[0][2], m1[1][2] + m2[1][2], m1[2][2] + m2[2][2]
        };
    }

    template<typename T>
    inline Matrix3<T> operator-(Matrix3<T> &m1, Matrix3<T> &m2) {
        return Matrix3<T>{
            m1[0][0] - m2[0][0], m1[1][0] - m2[1][0], m1[2][0] - m2[2][0],
            m1[0][1] - m2[0][1], m1[1][1] - m2[1][1], m1[2][1] - m2[2][1],
            m1[0][2] - m2[0][2], m1[1][2] - m2[1][2], m1[2][2] - m2[2][2]
        };
    }

    template<typename T>
    inline Matrix3<T> operator*(Matrix3<T> &m1, Matrix3<T> &m2) {
        return Matrix3<T>{
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],

            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],

            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
            m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2]
        };
    }

    template<typename T>
    inline Matrix3<T> operator+(Matrix3<T> &m, T &n) {
        return Matrix3<T>{
            m[0][0] + n, m[1][0] + n, m[2][0] + n,
            m[0][1] + n, m[1][1] + n, m[2][1] + n,
            m[0][2] + n, m[1][2] + n, m[2][2] + n
        };
    }

    template<typename T>
    inline Matrix3<T> operator+(T &n, Matrix3<T> &m) {
        return m + n;
    }

    template<typename T>
    inline Matrix3<T> operator-(Matrix3<T> &m, T &n) {
        return Matrix3<T>{
            m[0][0] - n, m[1][0] - n, m[2][0] - n,
            m[0][1] - n, m[1][1] - n, m[2][1] - n,
            m[0][2] - n, m[1][2] - n, m[2][2] - n
        };
    }

    template<typename T>
    inline Matrix3<T> operator-(T &n, Matrix3<T> &m) {
        return Matrix3<T>{
            n - m[0][0], n - m[1][0], n - m[2][0],
            n - m[0][1], n - m[1][1], n - m[2][1],
            n - m[0][2], n - m[1][2], n - m[2][2]
        };
    }

    template<typename T>
    inline Matrix3<T> operator*(Matrix3<T> &m, T &n) {
        return Matrix3<T>{
            m[0][0] * n, m[1][0] * n, m[2][0] * n,
            m[0][1] * n, m[1][1] * n, m[2][1] * n,
            m[0][2] * n, m[1][2] * n, m[2][2] * n
        };
    }

    template<typename T>
    inline Matrix3<T> operator*(T &n, Matrix3<T> &m) {
        return m * n;
    }

    template<typename T>
    inline Matrix3<T> operator/(Matrix3<T> &m, T &n) {
        return Matrix3<T>{
            m[0][0] / n, m[1][0] / n, m[2][0] / n,
            m[0][1] / n, m[1][1] / n, m[2][1] / n,
            m[0][2] / n, m[1][2] / n, m[2][2] / n
        };
    }

    template<typename T>
    inline Matrix3<T> operator/(T &n, Matrix3<T> &m) {
        return Matrix3<T>{
            n / m[0][0], n / m[1][0], n / m[2][0],
            n / m[0][1], n / m[1][1], n / m[2][1],
            n / m[0][2], n / m[1][2], n / m[2][2]
        };
    }
}
