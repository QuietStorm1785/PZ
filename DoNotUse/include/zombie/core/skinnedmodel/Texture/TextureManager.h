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


class TextureManager {
public:
    static TextureManager Instance = std::make_shared<TextureManager>();
   public std::unordered_map<std::string, Texture2D> Textures = std::make_unique<std::unordered_map<>>();

    bool AddTexture(const std::string& var1) {
    Texture var2 = Texture.getSharedTexture(var1);
      if (var2 == nullptr) {
    return false;
      } else {
         this.Textures.put(var1, std::make_shared<Texture2D>(var2));
    return true;
      }
   }

    void AddTexture(const std::string& var1, Texture var2) {
      if (!this.Textures.containsKey(var1)) {
         this.Textures.put(var1, std::make_shared<Texture2D>(var2));
      }
   }
}
} // namespace Texture
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
