#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"

namespace zombie {
namespace iso {


class IsoMetaGrid {
public:
    static const short VZF_FaceDirection = 1;
    IsoDirections dir = IsoDirections.Max;
    short flags = 0;

   public IsoMetaGrid$VehicleZone(std::string var1, std::string var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      super(var1, var2, var3, var4, var5, var6, var7);
      if (var8 != nullptr) {
    void* var9 = var8.rawget("Direction");
         if (dynamic_cast<std*>(var9) != nullptr::string) {
            this.dir = IsoDirections.valueOf((std::string)var9);
         }

         var9 = var8.rawget("FaceDirection");
         if (var9 == bool.TRUE) {
            this.flags = (short)(this.flags | 1);
         }
      }
   }

    bool isFaceDirection() {
      return (this.flags & 1) != 0;
   }
}
} // namespace iso
} // namespace zombie
