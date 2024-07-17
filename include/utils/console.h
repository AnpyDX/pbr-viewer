/**
* >> PBR-Viewer
* 
* @biref Console Output Utility
*/

#pragma once
#include <iostream>

namespace PBRV {
    /** Console Utiility */
    struct UConsole {
        template <typename T>
        static void debug(const T& msg) {
            std::cout << "\033[1;32m[ Debug ]\033[m " << msg << std::endl;
        }

        template <typename T>
        static void warning(const T& msg) {
            std::cerr << "\033[1;32;31m[ Warning ]\033[m " << msg << std::endl;
        }
    };
}