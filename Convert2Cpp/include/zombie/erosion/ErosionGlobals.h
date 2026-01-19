#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/season/ErosionIceQueen.h"
#include "zombie/erosion/season/ErosionSeason.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"

namespace zombie {
namespace erosion {


class ErosionGlobals {
public:
    static bool EROSION_DEBUG = true;

    static void Boot(IsoSpriteManager var0) {
    new ErosionMain();
   }

    static void Reset() {
      ErosionMain.Reset();
      ErosionClient.Reset();
      ErosionIceQueen.Reset();
      ErosionSeason.Reset();
      ErosionRegions.Reset();
   }
}
} // namespace erosion
} // namespace zombie
