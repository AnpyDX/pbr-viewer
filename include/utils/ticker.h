/** PBRV Project (https://github.com/anpydx/pbr-viewer)
 * @brief FPS ticker object
 */

#pragma once
#include <array>
#include <numeric>

namespace PBRV {
    template <uint8_t CacheSize>
    struct UFPSTicker {
        std::array<float, CacheSize> cache { 0.0f };
        uint8_t current_index = 0;

        void set_tick(float tick) {
            cache[current_index] = (tick + cache[current_index]) / 2;
            current_index++;
            if (current_index == CacheSize) {
                current_index = 0;
            }
        }

        float get_avg() {
            return std::accumulate(cache.begin(), cache.end(), 0) / CacheSize;
        }
    };

    struct UIDTicker {
        int index = 1;
        int get() {
            return index++;
        }
    };
}