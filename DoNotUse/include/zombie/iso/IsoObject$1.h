#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoObject/IsoObjectFactory.h"

namespace zombie {
namespace iso {


class IsoObject {
public:
   IsoObject$1(byte var1, std::string var2) {
      super(var1, var2);
   }

    IsoObject InstantiateObject(IsoCell var1) {
    IsoObject var2 = IsoObject.getNew();
      var2.sx = 0.0F;
    return var2;
   }
}
} // namespace iso
} // namespace zombie
