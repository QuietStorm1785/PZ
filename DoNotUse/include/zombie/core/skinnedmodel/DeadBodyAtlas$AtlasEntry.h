#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/DeadBodyAtlas/Atlas.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    Atlas atlas;
    std::string key;
    std::string lightKey;
    int updateCounter;
    int x;
    int y;
    int w;
    int h;
    float offsetX;
    float offsetY;
    Texture tex;
    bool ready = false;

   private DeadBodyAtlas$AtlasEntry() {
   }

    void Reset() {
      this.atlas = nullptr;
      this.tex.destroy();
      this.tex = nullptr;
      this.ready = false;
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
