#pragma once
#include "zombie/erosion/season/ErosionIceQueen.h"
#include "zombie/erosion/season/ErosionSeason.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace erosion {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ErosionGlobals {
public:
  static bool EROSION_DEBUG = true;

  static void Boot(IsoSpriteManager spriteManager) { new ErosionMain(); }

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
