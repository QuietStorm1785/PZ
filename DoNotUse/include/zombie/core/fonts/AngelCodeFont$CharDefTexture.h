#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"

namespace zombie {
namespace core {
namespace fonts {


class AngelCodeFont {
public:
   public AngelCodeFont$CharDefTexture(TextureID var1, std::string var2) {
      super(var1, var2);
   }

    void releaseCharDef() {
      this.removeDependency(this.dataid);
   }
}
} // namespace fonts
} // namespace core
} // namespace zombie
