#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace scripting {
namespace objects {

class VehicleScript {
public:
    bool openable;

   VehicleScript$Window makeCopy() {
      VehicleScript$Window var1 = new VehicleScript$Window();
      var1.openable = this.openable;
    return var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
