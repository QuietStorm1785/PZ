#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/Vector2.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSUtilityVehicle/Params.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawner/Element.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class RVSUtilityVehicle : public RandomizedVehicleStoryBase {
public:
   private std::vector<std::string> tools = nullptr;
   private std::vector<std::string> carpenterTools = nullptr;
    Params params = std::make_shared<Params>();

    public RVSUtilityVehicle() {
      this.name = "Utility Vehicle";
      this.minZoneWidth = 8;
      this.minZoneHeight = 9;
      this.setChance(7);
      this.tools = std::make_unique<std::vector<>>();
      this.tools.push_back("Base.PickAxe");
      this.tools.push_back("Base.Shovel");
      this.tools.push_back("Base.Shovel2");
      this.tools.push_back("Base.Hammer");
      this.tools.push_back("Base.LeadPipe");
      this.tools.push_back("Base.PipeWrench");
      this.tools.push_back("Base.Sledgehammer");
      this.tools.push_back("Base.Sledgehammer2");
      this.carpenterTools = std::make_unique<std::vector<>>();
      this.carpenterTools.push_back("Base.Hammer");
      this.carpenterTools.push_back("Base.NailsBox");
      this.carpenterTools.push_back("Base.Plank");
      this.carpenterTools.push_back("Base.Plank");
      this.carpenterTools.push_back("Base.Plank");
      this.carpenterTools.push_back("Base.Screwdriver");
      this.carpenterTools.push_back("Base.Saw");
      this.carpenterTools.push_back("Base.Saw");
      this.carpenterTools.push_back("Base.Woodglue");
   }

    void randomizeVehicleStory(Zone var1, IsoChunk var2) {
      this.callVehicleStorySpawner(var1, var2, 0.0F);
   }

   public void doUtilityVehicle(
      Zone var1, IsoChunk var2, std::string var3, std::string var4, std::string var5, int var6, std::string var7, std::vector<std::string> var8, int var9, boolean var10
   ) {
      this.params.zoneName = var3;
      this.params.scriptName = var4;
      this.params.outfits = var5;
      this.params.femaleChance = var6;
      this.params.vehicleDistrib = var7;
      this.params.items = var8;
      this.params.nbrOfItem = var9;
      this.params.addTrailer = var10;
   }

    bool initVehicleStorySpawner(Zone var1, IsoChunk var2, bool var3) {
    int var4 = Rand.Next(0, 7);
      switch (var4) {
         case 0:
            this.doUtilityVehicle(var1, var2, nullptr, "Base.PickUpTruck", "ConstructionWorker", 0, "ConstructionWorker", this.tools, Rand.Next(0, 3), true);
            break;
         case 1:
            this.doUtilityVehicle(var1, var2, "police", nullptr, "Police", nullptr, nullptr, nullptr, 0, false);
            break;
         case 2:
            this.doUtilityVehicle(var1, var2, "fire", nullptr, "Fireman", nullptr, nullptr, nullptr, 0, false);
            break;
         case 3:
            this.doUtilityVehicle(var1, var2, "ranger", nullptr, "Ranger", nullptr, nullptr, nullptr, 0, true);
            break;
         case 4:
            this.doUtilityVehicle(var1, var2, "mccoy", nullptr, "McCoys", 0, "Carpenter", this.carpenterTools, Rand.Next(2, 6), true);
            break;
         case 5:
            this.doUtilityVehicle(var1, var2, "postal", nullptr, "Postal", nullptr, nullptr, nullptr, 0, false);
            break;
         case 6:
            this.doUtilityVehicle(var1, var2, "fossoil", nullptr, "Fossoil", nullptr, nullptr, nullptr, 0, false);
      }

    VehicleStorySpawner var5 = VehicleStorySpawner.getInstance();
      var5.clear();
    Vector2 var6 = IsoDirections.N.ToVector();
    float var7 = (float) (Math.PI / 6);
      if (var3) {
         var7 = 0.0F;
      }

      var6.rotate(Rand.Next(-var7, var7));
    float var8 = -2.0F;
    uint8_t var9 = 5;
      var5.addElement("vehicle1", 0.0F, var8, var6.getDirection(), 2.0F, var9);
      if (this.params.addTrailer && Rand.NextBool(7)) {
    uint8_t var10 = 3;
         var5.addElement("trailer", 0.0F, var8 + var9 / 2.0F + 1.0F + var10 / 2.0F, var6.getDirection(), 2.0F, var10);
      }

      if (this.params.items != nullptr) {
         for (int var11 = 0; var11 < this.params.nbrOfItem; var11++) {
            var5.addElement("tool", Rand.Next(-3.5F, 3.5F), Rand.Next(-3.5F, 3.5F), 0.0F, 1.0F, 1.0F);
         }
      }

      var5.setParameter("zone", var1);
    return true;
   }

    void spawnElement(VehicleStorySpawner var1, Element var2) {
    IsoGridSquare var3 = var2.square;
      if (var3 != nullptr) {
    float var4 = var2.z;
    Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
    BaseVehicle var6 = (BaseVehicle)var1.getParameter("vehicle1", BaseVehicle.class);
    std::string var7 = var2.id;
         switch (var7) {
            case "tool":
               if (var6 != nullptr) {
    float var9 = PZMath.max(var2.position.x - var3.x, 0.001F);
    float var10 = PZMath.max(var2.position.y - var3.y, 0.001F);
    float var11 = 0.0F;
                  var3.AddWorldInventoryItem((std::string)PZArrayUtil.pickRandom(this.params.items), var9, var10, var11);
               }
               break;
            case "trailer":
               if (var6 != nullptr) {
                  this.addTrailer(
                     var6, var5, var3.getChunk(), this.params.zoneName, this.params.vehicleDistrib, Rand.NextBool(1) ? "Base.Trailer" : "Base.TrailerCover"
                  );
               }
               break;
            case "vehicle1":
               var6 = this.addVehicle(
                  var5, var2.position.x, var2.position.y, var4, var2.direction, this.params.zoneName, this.params.scriptName, nullptr, this.params.vehicleDistrib
               );
               if (var6 != nullptr) {
                  this.addZombiesOnVehicle(Rand.Next(2, 5), this.params.outfits, this.params.femaleChance, var6);
               }
         }
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
