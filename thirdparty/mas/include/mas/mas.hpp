/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: the entry of mas-lib
*/

#pragma once

/**
 * @section Including Types & Utilities
 */
#include "types/shared_common.hpp"
#include "utils/common.hpp"

/**
 * @section Universal Types Macro
 */
namespace mas {

#if defined(MAS_UTYPE_INT)
    using vec2 = Vector2<int>;
    using vec3 = Vector3<int>;
    using vec4 = Vector4<int>;
    using mat2 = Matrix2<int>;
    using mat3 = Matrix3<int>;
    using mat4 = Matrix4<int>;

#elif defined(MAS_UTYPE_FLOAT)
    using vec2 = Vector2<float>;
    using vec3 = Vector3<float>;
    using vec4 = Vector4<float>;
    using mat2 = Matrix2<float>;
    using mat3 = Matrix3<float>;
    using mat4 = Matrix4<float>;

#elif defined(MAS_UTYPE_DOUBLE)
    using vec2 = Vector2<double>;
    using vec3 = Vector3<double>;
    using vec4 = Vector4<double>;
    using mat2 = Matrix2<double>;
    using mat3 = Matrix3<double>;
    using mat4 = Matrix4<double>;

#endif

}