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
   VehicleScript$Door makeCopy() {
      return new VehicleScript$Door();
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
