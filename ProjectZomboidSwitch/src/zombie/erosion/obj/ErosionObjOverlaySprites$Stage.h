#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/obj/ErosionObjOverlaySprites/Sprite.h"

namespace zombie {
namespace erosion {
namespace obj {


class ErosionObjOverlaySprites {
public:
   public Sprite[] seasons = new Sprite[6];

   private ErosionObjOverlaySprites$Stage() {
   }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
