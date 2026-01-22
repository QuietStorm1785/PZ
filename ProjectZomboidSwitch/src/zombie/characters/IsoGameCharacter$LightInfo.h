#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter/TorchInfo.h"
#include "zombie/iso/IsoGridSquare.h"

namespace zombie {
namespace characters {


class IsoGameCharacter {
public:
    IsoGridSquare square;
    float x;
    float y;
    float z;
    float angleX;
    float angleY;
   public std::vector<TorchInfo> torches = std::make_unique<std::vector<>>();
    long time;
    float night;
    float rmod;
    float gmod;
    float bmod;

    void initFrom(IsoGameCharacter$LightInfo var1) {
      this.square = var1.square;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.angleX = var1.angleX;
      this.angleY = var1.angleY;
      this.torches.clear();
      this.torches.addAll(var1.torches);
      this.time = (long)(System.nanoTime() / 1000000.0);
      this.night = var1.night;
      this.rmod = var1.rmod;
      this.gmod = var1.gmod;
      this.bmod = var1.bmod;
   }
}
} // namespace characters
} // namespace zombie
