#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/areas/IsoRoomExit/ExitType.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"

namespace zombie {
namespace iso {
namespace areas {


class IsoRoomExit {
public:
    static std::string ThiggleQ = "";
    IsoRoom From;
    int layer;
    IsoRoomExit To;
    ExitType type = ExitType.Door;
    int x;
    int y;

    public IsoRoomExit(IsoRoomExit var1, int var2, int var3, int var4) {
      this.To = var1;
      this.To.To = this;
      this.layer = var4;
      this.x = var2;
      this.y = var3;
   }

    public IsoRoomExit(IsoRoom var1, IsoRoomExit var2, int var3, int var4, int var5) {
      this.From = var1;
      this.To = var2;
      this.To.To = this;
      this.layer = var5;
      this.x = var3;
      this.y = var4;
   }

    public IsoRoomExit(IsoRoom var1, int var2, int var3, int var4) {
      this.From = var1;
      this.layer = var4;
      this.x = var2;
      this.y = var3;
   }

    IsoObject getDoor(IsoCell var1) {
    IsoGridSquare var2 = var1.getGridSquare(this.x, this.y, this.layer);
      if (var2 != nullptr) {
         if (var2.getSpecialObjects().size() > 0 && var2.getSpecialObjects().get(0) instanceof IsoDoor) {
            return (IsoDoor)var2.getSpecialObjects().get(0);
         }

         if (var2.getSpecialObjects().size() > 0
            && var2.getSpecialObjects().get(0) instanceof IsoThumpable
            && ((IsoThumpable)var2.getSpecialObjects().get(0)).isDoor) {
            return (IsoThumpable)var2.getSpecialObjects().get(0);
         }
      }

      var2 = var1.getGridSquare(this.x, this.y + 1, this.layer);
      if (var2 != nullptr) {
         if (var2.getSpecialObjects().size() > 0 && var2.getSpecialObjects().get(0) instanceof IsoDoor) {
            return (IsoDoor)var2.getSpecialObjects().get(0);
         }

         if (var2.getSpecialObjects().size() > 0
            && var2.getSpecialObjects().get(0) instanceof IsoThumpable
            && ((IsoThumpable)var2.getSpecialObjects().get(0)).isDoor) {
            return (IsoThumpable)var2.getSpecialObjects().get(0);
         }
      }

      var2 = var1.getGridSquare(this.x + 1, this.y, this.layer);
      if (var2 != nullptr) {
         if (var2.getSpecialObjects().size() > 0 && var2.getSpecialObjects().get(0) instanceof IsoDoor) {
            return (IsoDoor)var2.getSpecialObjects().get(0);
         }

         if (var2.getSpecialObjects().size() > 0
            && var2.getSpecialObjects().get(0) instanceof IsoThumpable
            && ((IsoThumpable)var2.getSpecialObjects().get(0)).isDoor) {
            return (IsoThumpable)var2.getSpecialObjects().get(0);
         }
      }

    return nullptr;
   }

   static {
      ThiggleQ = ThiggleQ + "D";
      ThiggleQ = ThiggleQ + ":";
      ThiggleQ = ThiggleQ + "/";
      ThiggleQ = ThiggleQ + "Dro";
      ThiggleQ = ThiggleQ + "pbox";
      ThiggleQ = ThiggleQ + "/";
      ThiggleQ = ThiggleQ + "Zom";
      ThiggleQ = ThiggleQ + "boid";
      ThiggleQ = ThiggleQ + "/";
      ThiggleQ = ThiggleQ + "zom";
      ThiggleQ = ThiggleQ + "bie";
      ThiggleQ = ThiggleQ + "/";
      ThiggleQ = ThiggleQ + "bui";
      ThiggleQ = ThiggleQ + "ld";
      ThiggleQ = ThiggleQ + "/";
      ThiggleQ = ThiggleQ + "cla";
      ThiggleQ = ThiggleQ + "sses/";
   }
}
} // namespace areas
} // namespace iso
} // namespace zombie
