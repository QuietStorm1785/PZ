#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare/GetSquare.h"

namespace zombie {
namespace iso {


class IsoGridSquare {
public:
    IsoGridSquare getGridSquare(int var1, int var2, int var3) {
      return IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
   }
}
} // namespace iso
} // namespace zombie
