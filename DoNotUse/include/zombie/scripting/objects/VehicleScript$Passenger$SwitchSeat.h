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
    std::string id;
    int seat;
    std::string anim;
    float rate = 1.0F;
    std::string sound;

    std::string getId() {
      return this.id;
   }

   public VehicleScript$Passenger$SwitchSeat makeCopy() {
      VehicleScript$Passenger$SwitchSeat var1 = new VehicleScript$Passenger$SwitchSeat();
      var1.id = this.id;
      var1.seat = this.seat;
      var1.anim = this.anim;
      var1.rate = this.rate;
      var1.sound = this.sound;
    return var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
