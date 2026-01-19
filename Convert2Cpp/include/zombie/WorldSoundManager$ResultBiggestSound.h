#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/WorldSoundManager/WorldSound.h"

namespace zombie {


class WorldSoundManager {
public:
    WorldSound sound;
    float attract;

   public WorldSoundManager$ResultBiggestSound init(WorldSound var1, float var2) {
      this.sound = var1;
      this.attract = var2;
    return this;
   }
}
} // namespace zombie
