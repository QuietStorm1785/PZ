#pragma once
#include "zombie/erosion/season/ErosionIceQueen.h"
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

class ErosionClient {
public:
  static ErosionClient instance;

public
  ErosionClient(IsoSpriteManager spriteManager, bool var2) {
    instance = this;
    new ErosionIceQueen();
    ErosionRegions.init();
  }

  static void Reset() { instance = nullptr; }
}
} // namespace erosion
} // namespace zombie
