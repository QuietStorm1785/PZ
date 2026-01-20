#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/Vector2.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawner/Element.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class RVSChangingTire : public RandomizedVehicleStoryBase {
public:
    public RVSChangingTire() {
      this.name = "Changing Tire";
      this.minZoneWidth = 5;
      this.minZoneHeight = 5;
      this.setChance(3);
   }

    void randomizeVehicleStory(Zone var1, IsoChunk var2) {
    float var3 = (float) (Math.PI / 6);
      this.callVehicleStorySpawner(var1, var2, Rand.Next(-var3, var3));
   }

    bool initVehicleStorySpawner(Zone var1, IsoChunk var2, bool var3) {
    VehicleStorySpawner var4 = VehicleStorySpawner.getInstance();
      var4.clear();
    bool var5 = Rand.NextBool(2);
      if (var3) {
         var5 = true;
      }

    int var6 = var5 ? 1 : -1;
    Vector2 var7 = IsoDirections.N.ToVector();
      var4.addElement("vehicle1", var6 * -1.5F, 0.0F, var7.getDirection(), 2.0F, 5.0F);
      var4.addElement("tire1", var6 * 0.0F, 0.0F, 0.0F, 1.0F, 1.0F);
      var4.addElement("tool1", var6 * 0.8F, -0.2F, 0.0F, 1.0F, 1.0F);
      var4.addElement("tool2", var6 * 1.2F, 0.2F, 0.0F, 1.0F, 1.0F);
      var4.addElement("tire2", var6 * 2.0F, 0.0F, 0.0F, 1.0F, 1.0F);
      var4.setParameter("zone", var1);
      var4.setParameter("removeRightWheel", var5);
    return true;
   }

    void spawnElement(VehicleStorySpawner var1, Element var2) {
    IsoGridSquare var3 = var2.square;
      if (var3 != nullptr) {
    float var4 = PZMath.max(var2.position.x - var3.x, 0.001F);
    float var5 = PZMath.max(var2.position.y - var3.y, 0.001F);
    float var6 = 0.0F;
    float var7 = var2.z;
    Zone var8 = (Zone)var1.getParameter("zone", Zone.class);
    bool var9 = var1.getParameterBoolean("removeRightWheel");
    BaseVehicle var10 = (BaseVehicle)var1.getParameter("vehicle1", BaseVehicle.class);
    std::string var11 = var2.id;
         switch (var11) {
            case "tire1":
               if (var10 != nullptr) {
    InventoryItem var16 = var3.AddWorldInventoryItem("Base.ModernTire" + var10.getScript().getMechanicType(), var4, var5, var6);
                  if (var16 != nullptr) {
                     var16.setItemCapacity(var16.getMaxCapacity());
                  }

                  this.addBloodSplat(var3, Rand.Next(10, 20));
               }
               break;
            case "tire2":
               if (var10 != nullptr) {
    InventoryItem var15 = var3.AddWorldInventoryItem("Base.OldTire" + var10.getScript().getMechanicType(), var4, var5, var6);
                  if (var15 != nullptr) {
                     var15.setCondition(0);
                  }
               }
               break;
            case "tool1":
               var3.AddWorldInventoryItem("Base.LugWrench", var4, var5, var6);
               break;
            case "tool2":
               var3.AddWorldInventoryItem("Base.Jack", var4, var5, var6);
               break;
            case "vehicle1":
               var10 = this.addVehicle(var8, var2.position.x, var2.position.y, var7, var2.direction, "good", nullptr, nullptr, nullptr);
               if (var10 != nullptr) {
                  var10.setGeneralPartCondition(0.7F, 40.0F);
                  var10.setRust(0.0F);
    VehiclePart var13 = var10.getPartById(var9 ? "TireRearRight" : "TireRearLeft");
                  var10.setTireRemoved(var13.getWheelIndex(), true);
                  var13.setModelVisible("InflatedTirePlusWheel", false);
                  var13.setInventoryItem(nullptr);
                  this.addZombiesOnVehicle(2, nullptr, nullptr, var10);
                  var1.setParameter("vehicle1", var10);
               }
         }
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
