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
    int capacity;
    int seat = -1;
    std::string seatID;
    std::string luaTest;
    std::string contentType;
    bool conditionAffectsCapacity = false;

   VehicleScript$Container makeCopy() {
      VehicleScript$Container var1 = new VehicleScript$Container();
      var1.capacity = this.capacity;
      var1.seat = this.seat;
      var1.seatID = this.seatID;
      var1.luaTest = this.luaTest;
      var1.contentType = this.contentType;
      var1.conditionAffectsCapacity = this.conditionAffectsCapacity;
    return var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
