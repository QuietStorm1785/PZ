#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoRoofFixer {
public:
    IsoGridSquare square;
    int floorType;

   private IsoRoofFixer$PlaceFloorInfo() {
   }

    void set(IsoGridSquare var1, int var2) {
      this.square = var1;
      this.floorType = var2;
   }
}
} // namespace iso
} // namespace zombie
