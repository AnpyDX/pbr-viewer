/**
* mas-lib (https://github.com/anpydx/mas)
*    a lightweight linear math library
* @copyright Copyright (c) 2023-2024 anpyd, All Rights Reserved.
*
* @version: 2.0
* @brief: angle convert utility
*/

#pragma once

#include "constants.hpp"

namespace mas {
    /**
     * @brief convert degress to radians
     * @param degress
     */
    template <typename T>
    inline T radians(const T& degress) {
        return static_cast<T>((degress / 180.0) * PI);
    }

    /**
     * @brief convert radians to degrees
     * @param radians
     */
    template <typename T>
    inline T degrees(const T& radians) {
        return static_cast<T>((radians / PI) * 180.0);
    }
}