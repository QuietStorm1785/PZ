#pragma once
#include <vector>
#include <memory>
#include "zombie/core/textures/Texture.h"
#include "zombie/erosion/utils/Noise2D.h"
#include "zombie/iso/IsoCell/SnowGridTiles.h"

namespace zombie {
namespace iso {

class IsoCell;

class SnowGrid {
public:
    int w = 256;
    int h = 256;
    int frac = 0;
    static constexpr int N = 0;
    static constexpr int S = 1;
    static constexpr int W = 2;
    static constexpr int E = 3;
    static constexpr int A = 0;
    static constexpr int B = 1;
    std::vector<std::vector<std::vector<std::shared_ptr<Texture>>>> grid;
    std::vector<std::vector<std::vector<int8_t>>> gridType;
    SnowGrid(IsoCell* cell, int var2) : grid(w, std::vector<std::vector<std::shared_ptr<Texture>>>(h, std::vector<std::shared_ptr<Texture>>(2))), gridType(w, std::vector<std::vector<int8_t>>(h, std::vector<int8_t>(2))) {}
    // Additional methods and fields as needed
};

} // namespace iso
} // namespace zombie
