#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerContainer.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerRoom.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSSpecificProfession : public RandomizedDeadSurvivorBase {
public:
   private const std::vector<std::string> specificProfessionDistribution = std::make_unique<std::vector<>>();

    void randomizeDeadSurvivor(BuildingDef var1) {
    IsoGridSquare var2 = var1.getFreeSquareInRoom();
      if (var2 != nullptr) {
    IsoDeadBody var3 = createRandomDeadBody(var2.getX(), var2.getY(), var2.getZ(), nullptr, 0);
         if (var3 != nullptr) {
    ItemPickerRoom var4 = (ItemPickerRoom)ItemPickerJava.rooms.get(PZArrayUtil.pickRandom(this.specificProfessionDistribution));
            ItemPickerJava.rollItem((ItemPickerContainer)var4.Containers.get("counter"), var3.getContainer(), true, nullptr, nullptr);
         }
      }
   }

    public RDSSpecificProfession() {
      this.specificProfessionDistribution.push_back("Carpenter");
      this.specificProfessionDistribution.push_back("Electrician");
      this.specificProfessionDistribution.push_back("Farmer");
      this.specificProfessionDistribution.push_back("Nurse");
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
