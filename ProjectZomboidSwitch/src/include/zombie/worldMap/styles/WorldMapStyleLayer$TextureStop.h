#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/Stop.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleLayer {
public:
    std::string texturePath;
    Texture texture;

   public WorldMapStyleLayer$TextureStop(float var1, std::string var2) {
      super(var1);
      this.texturePath = var2;
      this.texture = Texture.getTexture(var2);
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
