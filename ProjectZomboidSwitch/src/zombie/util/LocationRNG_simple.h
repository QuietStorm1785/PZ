#pragma once
#include <cstdint>
#include <cmath>

namespace zombie {
namespace util {

// Location-based random number generator using SplitMix64 and XorShift128+
class LocationRNG {
private:
    int64_t state;    // SplitMix64 state
    int64_t s0, s1;   // XorShift128+ state
    
    static constexpr float INT_TO_FLOAT = 1.1920929e-07f; // 2^-23
    
    int64_t nextSplitMix64() {
        int64_t z = (state += 0x9e3779b97f4a7c15LL);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9LL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebLL;
        return z ^ (z >> 31);
    }
    
    // Rotate left for 64-bit integer
    static int64_t rotateLeft(int64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

public:
    LocationRNG() : state(0), s0(0), s1(0) {
        setSeed(0);
    }
    
    explicit LocationRNG(int64_t seed) : state(0), s0(0), s1(0) {
        setSeed(seed);
    }
    
    void setSeed(int64_t seed) {
        state = seed;
        s0 = nextSplitMix64();
        s1 = nextSplitMix64();
    }
    
    int64_t getSeed() const {
        return state;
    }
    
    // XorShift128+ generator
    int32_t nextInt() {
        int64_t x = s0;
        int64_t y = s1;
        int64_t result = x + y;
        
        y ^= x;
        s0 = rotateLeft(x, 55) ^ y ^ (y << 14);
        s1 = rotateLeft(y, 36);
        
        return static_cast<int32_t>(result & 0xFFFFFFFFLL);
    }
    
    // Random int in range [0, max)
    int32_t nextInt(int32_t max) {
        if (max <= 0) return 0;
        return static_cast<int32_t>(static_cast<uint32_t>(nextInt()) % static_cast<uint32_t>(max));
    }
    
    // Random float in range [0.0, 1.0)
    float nextFloat() {
        return (static_cast<uint32_t>(nextInt()) >> 8) * INT_TO_FLOAT;
    }
    
    // Location-based seeding from coordinates
    int32_t nextInt(int32_t x, int32_t y, int32_t z, int32_t max) {
        // Hash coordinates to create seed
        int64_t seed = x;
        seed = seed * 31 + y;
        seed = seed * 31 + z;
        
        setSeed(seed);
        return nextInt(max);
    }
    
    // Global instance for convenience
    static LocationRNG& getInstance() {
        static LocationRNG instance;
        return instance;
    }
};

} // namespace util
} // namespace zombie
