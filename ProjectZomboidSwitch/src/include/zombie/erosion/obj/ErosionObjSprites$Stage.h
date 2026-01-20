#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/obj/ErosionObjSprites/Section.h"

namespace zombie {
namespace erosion {
namespace obj {


class ErosionObjSprites {
public:
   public Section[] sections = new Section[4];

   private ErosionObjSprites$Stage() {
   }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
