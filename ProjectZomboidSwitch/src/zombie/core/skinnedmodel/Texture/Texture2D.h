#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace Texture {


class Texture2D {
public:
    Texture tex;

    public Texture2D(Texture var1) {
      this.tex = var1;
   }

    int getWidth() {
      return this.tex.getWidth();
   }

    int getHeight() {
      return this.tex.getHeight();
   }

    int getTexture() {
      return this.tex.getID();
   }

    void Apply() {
   }
}
} // namespace Texture
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
