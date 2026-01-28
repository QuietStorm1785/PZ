
#pragma once
#include <vector>
#include <cstdint>
#include <random>
#include <chrono>
#include <stdexcept>


namespace zombie {
namespace core {
namespace RandNS {

class PZSeedGenerator {
public:
    // Generates a vector of random bytes as a seed, with fallback logic
    static std::vector<uint8_t> generateSeed(int size) {
        std::vector<uint8_t> seed(size);
        bool seeded = false;
        try {
            std::random_device rd;
            // Some platforms throw or always return zero/minimal entropy
            for (int i = 0; i < size; ++i) {
                auto val = rd();
                // If random_device is deterministic, fallback
                if (i == 0 && (val == 0 || val == static_cast<unsigned int>(-1))) {
                    throw std::runtime_error("random_device not available");
                }
                seed[i] = static_cast<uint8_t>(val);
            }
            seeded = true;
        } catch (...) {
            // Fallback: use mt19937 seeded with time
            auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            std::mt19937 mt(static_cast<unsigned int>(now));
            for (int i = 0; i < size; ++i) {
                seed[i] = static_cast<uint8_t>(mt());
            }
        }
        return seed;
    }
};
} // namespace RandNS
} // namespace core
} // namespace zombie
