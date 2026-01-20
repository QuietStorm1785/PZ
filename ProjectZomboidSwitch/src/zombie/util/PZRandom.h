#pragma once
#include <random>
#include <ctime>

namespace zombie {
namespace util {

class PZRandom {
private:
    std::mt19937 generator;
    std::uniform_real_distribution<float> floatDist;
    std::uniform_real_distribution<double> doubleDist;
    
public:
    PZRandom() : generator(static_cast<unsigned>(std::time(nullptr))),
                 floatDist(0.0f, 1.0f),
                 doubleDist(0.0, 1.0) {}
    
    explicit PZRandom(unsigned seed) : generator(seed),
                                       floatDist(0.0f, 1.0f),
                                       doubleDist(0.0, 1.0) {}
    
    // Set seed
    void setSeed(unsigned seed) {
        generator.seed(seed);
    }
    
    // Random integer in range [0, max)
    int nextInt(int max) {
        if (max <= 0) return 0;
        std::uniform_int_distribution<int> dist(0, max - 1);
        return dist(generator);
    }
    
    // Random integer in range [min, max)
    int nextInt(int min, int max) {
        if (min >= max) return min;
        std::uniform_int_distribution<int> dist(min, max - 1);
        return dist(generator);
    }
    
    // Random float in range [0.0, 1.0)
    float nextFloat() {
        return floatDist(generator);
    }
    
    // Random double in range [0.0, 1.0)
    double nextDouble() {
        return doubleDist(generator);
    }
    
    // Random boolean
    bool nextBool() {
        return generator() % 2 == 0;
    }
};

// Global random instance
extern PZRandom GlobalRandom;

} // namespace util
} // namespace zombie
