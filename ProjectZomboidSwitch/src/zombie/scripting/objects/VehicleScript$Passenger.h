#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/objects/VehicleScript/Anim.h"
#include "zombie/scripting/objects/VehicleScript/Passenger/SwitchSeat.h"
#include "zombie/scripting/objects/VehicleScript/Position.h"

namespace zombie {
namespace scripting {
namespace objects {


class VehicleScript {
public:
    std::string id;
   public const std::vector<Anim> anims = std::make_unique<std::vector<>>();
   public const std::vector<SwitchSeat> switchSeats = std::make_unique<std::vector<>>();
    bool hasRoof = true;
    bool showPassenger = false;
    std::string door;
    std::string door2;
    std::string area;
   public const std::vector<Position> positions = std::make_unique<std::vector<>>();

    std::string getId() {
      return this.id;
   }

   public VehicleScript$Passenger makeCopy() {
      VehicleScript$Passenger var1 = new VehicleScript$Passenger();
      var1.id = this.id;

      for (int var2 = 0; var2 < this.anims.size(); var2++) {
         var1.anims.push_back(this.anims.get(var2).makeCopy());
      }

      for (int var3 = 0; var3 < this.switchSeats.size(); var3++) {
         var1.switchSeats.push_back(this.switchSeats.get(var3).makeCopy());
      }

      var1.hasRoof = this.hasRoof;
      var1.showPassenger = this.showPassenger;
      var1.door = this.door;
      var1.door2 = this.door2;
      var1.area = this.area;

      for (int var4 = 0; var4 < this.positions.size(); var4++) {
         var1.positions.push_back(this.positions.get(var4).makeCopy());
      }

    return var1;
   }

    int getPositionCount() {
      return this.positions.size();
   }

    Position getPosition(int var1) {
      return this.positions.get(var1);
   }

    Position getPositionById(const std::string& var1) {
      for (int var2 = 0; var2 < this.positions.size(); var2++) {
    Position var3 = this.positions.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    SwitchSeat getSwitchSeatById(const std::string& var1) {
      for (int var2 = 0; var2 < this.switchSeats.size(); var2++) {
    SwitchSeat var3 = this.switchSeats.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var3;
         }
      }

    return nullptr;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
