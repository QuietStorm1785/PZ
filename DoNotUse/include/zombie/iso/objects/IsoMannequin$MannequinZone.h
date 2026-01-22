#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoMannequin {
public:
    int bFemale = -1;
    IsoDirections dir = IsoDirections.Max;
    std::string mannequinScript = nullptr;
    std::string pose = nullptr;
    std::string skin = nullptr;
    std::string outfit = nullptr;

   public IsoMannequin$MannequinZone(std::string var1, std::string var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      super(var1, var2, var3, var4, var5, var6, var7);
      if (var8 != nullptr) {
    void* var9 = var8.rawget("Female");
         if (dynamic_cast<bool*>(var9) != nullptr) {
            this.bFemale = var9 == bool.TRUE ? 1 : 0;
         }

         var9 = var8.rawget("Direction");
         if (dynamic_cast<std*>(var9) != nullptr::string) {
            this.dir = IsoDirections.valueOf((std::string)var9);
         }

         var9 = var8.rawget("Outfit");
         if (dynamic_cast<std*>(var9) != nullptr::string) {
            this.outfit = (std::string)var9;
         }

         var9 = var8.rawget("Script");
         if (dynamic_cast<std*>(var9) != nullptr::string) {
            this.mannequinScript = (std::string)var9;
         }

         var9 = var8.rawget("Skin");
         if (dynamic_cast<std*>(var9) != nullptr::string) {
            this.skin = (std::string)var9;
         }

         var9 = var8.rawget("Pose");
         if (dynamic_cast<std*>(var9) != nullptr::string) {
            this.pose = (std::string)var9;
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
