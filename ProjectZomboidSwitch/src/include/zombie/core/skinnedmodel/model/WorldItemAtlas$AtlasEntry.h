#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/Atlas.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class WorldItemAtlas {
public:
    Atlas atlas;
    std::string key;
    int x;
    int y;
    int w;
    int h;
    float offsetX;
    float offsetY;
    Texture tex;
    bool ready = false;
    bool bRenderMainOK = false;
    bool bTooBig = false;

   private WorldItemAtlas$AtlasEntry() {
   }

    void Reset() {
      this.atlas = nullptr;
      this.tex.destroy();
      this.tex = nullptr;
      this.ready = false;
      this.bRenderMainOK = false;
      this.bTooBig = false;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
