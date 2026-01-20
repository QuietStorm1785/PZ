#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoObject/IsoObjectFactory.h"
#include "zombie/iso/objects/IsoJukebox.h"

namespace zombie {
namespace iso {


class IsoObject {
public:
   IsoObject$8(byte var1, std::string var2) {
      super(var1, var2);
   }

    IsoObject InstantiateObject(IsoCell var1) {
      return std::make_shared<IsoJukebox>(var1);
   }
}
} // namespace iso
} // namespace zombie
