/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: type defination of Matrix 4x4
*/

#pragma once

namespace mas {
    template<typename T>
    class Matrix4 {
    public:
        Matrix4() {
            for (auto &i: value) {
                i[0] = 0;
                i[1] = 0;
                i[2] = 0;
                i[3] = 0;
            }
        }

        Matrix4(const Matrix4 &m) {
            for (int i = 0; i < 4; i++) {
                value[i][0] = m.value[i][0];
                value[i][1] = m.value[i][1];
                value[i][2] = m.value[i][2];
                value[i][3] = m.value[i][3];
            }
        }

        Matrix4(
            const T &x0, const T &y0, const T &z0, const T &w0,
            const T &x1, const T &y1, const T &z1, const T &w1,
            const T &x2, const T &y2, const T &z2, const T &w2,
            const T &x3, const T &y3, const T &z3, const T &w3) {
            value[0][0] = x0;
            value[0][1] = x1;
            value[0][2] = x2;
            value[0][3] = x3;
            value[1][0] = y0;
            value[1][1] = y1;
            value[1][2] = y2;
            value[1][3] = y3;
            value[2][0] = z0;
            value[2][1] = z1;
            value[2][2] = z2;
            value[2][3] = z3;
            value[3][0] = w0;
            value[3][1] = w1;
            value[3][2] = w2;
            value[3][3] = w3;
        }

        explicit Matrix4(const T &scalar) {
            value[0][0] = scalar;
            value[0][1] = 0;
            value[0][2] = 0;
            value[0][3] = 0;
            value[1][0] = 0;
            value[1][1] = scalar;
            value[1][2] = 0;
            value[1][3] = 0;
            value[2][0] = 0;
            value[2][1] = 0;
            value[2][2] = scalar;
            value[2][3] = 0;
            value[3][0] = 0;
            value[3][1] = 0;
            value[3][2] = 0;
            value[3][3] = scalar;
        }

        T *operator[](const int &index) {
            return value[index];
        }

    private:
        /**
         * Matrix 4x4
         * Memory Layout
         *  [0]  [1]  [2]  [3]
         *  x0   y0   z0   w0
         *  x1   y1   z1   w1
         *  x2   y2   z2   w2
         *  x3   y3   z3   w3
         */
        T value[4][4];
    };

    template<typename T>
    inline Matrix4<T> operator+(Matrix4<T> &m1, Matrix4<T> &m2) {
        return Matrix4<T>{
            m1[0][0] + m2[0][0], m1[1][0] + m2[1][0], m1[2][0] + m2[2][0], m1[3][0] + m2[3][0],
            m1[0][1] + m2[0][1], m1[1][1] + m2[1][1], m1[2][1] + m2[2][1], m1[3][1] + m2[3][1],
            m1[0][2] + m2[0][2], m1[1][2] + m2[1][2], m1[2][2] + m2[2][2], m1[3][2] + m2[3][2],
            m1[0][3] + m2[0][3], m1[1][3] + m2[1][3], m1[2][3] + m2[2][3], m1[3][3] + m2[3][3]
        };
    }

    template<typename T>
    inline Matrix4<T> operator-(Matrix4<T> &m1, Matrix4<T> &m2) {
        return Matrix4<T>{
            m1[0][0] - m2[0][0], m1[1][0] - m2[1][0], m1[2][0] - m2[2][0], m1[3][0] - m2[3][0],
            m1[0][1] - m2[0][1], m1[1][1] - m2[1][1], m1[2][1] - m2[2][1], m1[3][1] - m2[3][1],
            m1[0][2] - m2[0][2], m1[1][2] - m2[1][2], m1[2][2] - m2[2][2], m1[3][2] - m2[3][2],
            m1[0][3] - m2[0][3], m1[1][3] - m2[1][3], m1[2][3] - m2[2][3], m1[3][3] - m2[3][3]
        };
    }

    template<typename T>
    inline Matrix4<T> operator*(Matrix4<T> &m1, Matrix4<T> &m2) {
        return Matrix4<T>{
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
            m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
            m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
            m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3],

            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
            m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
            m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
            m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3],

            m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
            m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
            m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
            m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] + m1[3][2] * m2[3][3],

            m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
            m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3],
            m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3],
            m1[0][3] * m2[3][0] + m1[1][3] * m2[3][1] + m1[2][3] * m2[3][2] + m1[3][3] * m2[3][3]
        };
    }

    template<typename T>
    inline Matrix4<T> operator+(Matrix4<T> &m, T &n) {
        return Matrix4<T>{
            m[0][0] + n, m[1][0] + n, m[2][0] + n, m[3][0] + n,
            m[0][1] + n, m[1][1] + n, m[2][1] + n, m[3][1] + n,
            m[0][2] + n, m[1][2] + n, m[2][2] + n, m[3][2] + n,
            m[0][3] + n, m[1][3] + n, m[2][3] + n, m[3][3] + n
        };
    }

    template<typename T>
    inline Matrix4<T> operator+(T &n, Matrix4<T> &m) {
        return m + n;
    }

    template<typename T>
    inline Matrix4<T> operator-(Matrix4<T> &m, T &n) {
        return Matrix4<T>{
            m[0][0] - n, m[1][0] - n, m[2][0] - n, m[3][0] - n,
            m[0][1] - n, m[1][1] - n, m[2][1] - n, m[3][1] - n,
            m[0][2] - n, m[1][2] - n, m[2][2] - n, m[3][2] - n,
            m[0][3] - n, m[1][3] - n, m[2][3] - n, m[3][3] - n
        };
    }

    template<typename T>
    inline Matrix4<T> operator-(T &n, Matrix4<T> &m) {
        return Matrix4<T>{
            n - m[0][0], n - m[1][0], n - m[2][0], n - m[3][0],
            n - m[0][1], n - m[1][1], n - m[2][1], n - m[3][1],
            n - m[0][2], n - m[1][2], n - m[2][2], n - m[3][2],
            n - m[0][3], n - m[1][3], n - m[2][3], n - m[3][3]
        };
    }

    template<typename T>
    inline Matrix4<T> operator*(Matrix4<T> &m, T &n) {
        return Matrix4<T>{
            m[0][0] * n, m[1][0] * n, m[2][0] * n, m[3][0] * n,
            m[0][1] * n, m[1][1] * n, m[2][1] * n, m[3][1] * n,
            m[0][2] * n, m[1][2] * n, m[2][2] * n, m[3][2] * n,
            m[0][3] * n, m[1][3] * n, m[2][3] * n, m[3][3] * n
        };
    }

    template<typename T>
    inline Matrix4<T> operator*(T &n, Matrix4<T> &m) {
        return m * n;
    }

    template<typename T>
    inline Matrix4<T> operator/(Matrix4<T> &m, T &n) {
        return Matrix4<T>{
            m[0][0] / n, m[1][0] / n, m[2][0] / n, m[3][0] / n,
            m[0][1] / n, m[1][1] / n, m[2][1] / n, m[3][1] / n,
            m[0][2] / n, m[1][2] / n, m[2][2] / n, m[3][2] / n,
            m[0][3] / n, m[1][3] / n, m[2][3] / n, m[3][3] / n
        };
    }

    template<typename T>
    inline Matrix4<T> operator/(T &n, Matrix4<T> &m) {
        return Matrix4<T>{
            n / m[0][0], n / m[1][0], n / m[2][0], n / m[3][0],
            n / m[0][1], n / m[1][1], n / m[2][1], n / m[3][1],
            n / m[0][2], n / m[1][2], n / m[2][2], n / m[3][2],
            n / m[0][3], n / m[1][3], n / m[2][3], n / m[3][3]
        };
    }
}
