#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/season/ErosionIceQueen.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"

namespace zombie {
namespace erosion {


class ErosionClient {
:
    static ErosionClient instance;

     ErosionClient(IsoSpriteManager var1, bool var2) {
      instance = this;
    new ErosionIceQueen();
      ErosionRegions.init();
   }

    static void Reset() {
      instance = nullptr;
   }
}
} // namespace erosion
} // namespace zombie
