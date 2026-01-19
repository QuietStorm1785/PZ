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
:
    WorldSound sound;
    float attract;

    WorldSoundManager$ResultBiggestSound init(WorldSound var1, float var2) {
      this.sound = var1;
      this.attract = var2;
    return this;
   }
}
} // namespace zombie
