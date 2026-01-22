#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/WorldSoundManager/WorldSound.h"

namespace zombie {
namespace popman {


class MPDebugInfo {
public:
    int x;
    int y;
    int radius;
    bool bRepeating;
    bool sourceIsZombie;

   MPDebugInfo$MPSoundDebugInfo(WorldSound var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.radius = var1.radius;
      this.bRepeating = var1.bRepeating;
      this.sourceIsZombie = var1.sourceIsZombie;
   }
}
} // namespace popman
} // namespace zombie
