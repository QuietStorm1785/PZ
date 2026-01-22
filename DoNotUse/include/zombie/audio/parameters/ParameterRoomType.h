#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/audio/parameters/ParameterRoomType/RoomType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoMetaGrid/RoomTone.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterRoomType : public FMODGlobalParameter {
public:
    static ParameterRoomType instance;
    static RoomType roomType = nullptr;

    public ParameterRoomType() {
      super("RoomType");
      instance = this;
   }

    float calculateCurrentValue() {
      return this.getRoomType().label;
   }

    RoomType getRoomType() {
      if (roomType != nullptr) {
    return roomType;
      } else {
    IsoGameCharacter var1 = this.getCharacter();
         if (var1 == nullptr) {
            return RoomType.Generic;
         } else {
    BuildingDef var2 = var1.getCurrentBuildingDef();
            if (var2 == nullptr) {
               return RoomType.Generic;
            } else {
    IsoMetaGrid var3 = IsoWorld.instance.getMetaGrid();
    IsoMetaCell var4 = var3.getCellData(PZMath.fastfloor(var1.x / 300.0F), PZMath.fastfloor(var1.y / 300.0F));
               if (var4 != nullptr && !var4.roomTones.empty()) {
    RoomDef var5 = var1.getCurrentRoomDef();
    RoomTone var6 = nullptr;

                  for (int var7 = 0; var7 < var4.roomTones.size(); var7++) {
    RoomTone var8 = (RoomTone)var4.roomTones.get(var7);
    RoomDef var9 = var3.getRoomAt(var8.x, var8.y, var8.z);
                     if (var9 != nullptr) {
                        if (var9 == var5) {
                           return RoomType.valueOf(var8.enumValue);
                        }

                        if (var8.entireBuilding && var9.building == var2) {
                           var6 = var8;
                        }
                     }
                  }

                  return var6 != nullptr ? RoomType.valueOf(var6.enumValue) : RoomType.Generic;
               } else {
                  return RoomType.Generic;
               }
            }
         }
      }
   }

    IsoGameCharacter getCharacter() {
    IsoPlayer var1 = nullptr;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
         if (var3 != nullptr && (var1 == nullptr || var1.isDead() && var3.isAlive() || var1.Traits.Deaf.isSet() && !var3.Traits.Deaf.isSet())) {
            var1 = var3;
         }
      }

    return var1;
   }

    static void setRoomType(int var0) {
      try {
         roomType = RoomType.values()[var0];
      } catch (ArrayIndexOutOfBoundsException var2) {
         roomType = nullptr;
      }
   }

    static void render(IsoPlayer var0) {
      if (instance != nullptr) {
         if (var0 == instance.getCharacter()) {
            var0.drawDebugTextBelow("RoomType : " + instance.getRoomType().name());
         }
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
