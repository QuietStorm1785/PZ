#pragma once
#include <vector>
#include <memory>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace iso {

class IsoCell;

class SnowGridTiles {
public:
    int8_t ID = -1;
    int counter = -1;
    std::vector<std::shared_ptr<Texture>> textures;
    SnowGridTiles(IsoCell* cell, int8_t id) : ID(id) {}
    void add(std::shared_ptr<Texture> tex) { textures.push_back(tex); }
    std::shared_ptr<Texture> getNext() {
        counter++;
        if (counter >= static_cast<int>(textures.size())) counter = 0;
        return textures[counter];
    }
    std::shared_ptr<Texture> get(int idx) { return textures[idx]; }
    int size() const { return static_cast<int>(textures.size()); }
};

} // namespace iso
} // namespace zombie
