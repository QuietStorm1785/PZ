#pragma once
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace Texture {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextureManager {
public:
  static TextureManager Instance = new TextureManager();
public
  HashMap<String, Texture2D> Textures = std::make_unique<HashMap<>>();

  bool AddTexture(const std::string &string) {
    Texture texture = Texture.getSharedTexture(string);
    if (texture == nullptr) {
      return false;
    } else {
      this.Textures.put(string, new Texture2D(texture));
      return true;
    }
  }

  void AddTexture(const std::string &string, Texture texture) {
    if (!this.Textures.containsKey(string)) {
      this.Textures.put(string, new Texture2D(texture));
    }
  }
}
} // namespace Texture
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
