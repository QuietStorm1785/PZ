#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"

namespace fmod {
namespace fmod {


class FMODFootstep {
public:
    std::string wood;
    std::string concrete;
    std::string grass;
    std::string upstairs;
    std::string woodCreak;

    public FMODFootstep(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      this.grass = var1;
      this.wood = var2;
      this.concrete = var3;
      this.upstairs = var4;
      this.woodCreak = "HumanFootstepFloorCreaking";
   }

    bool isUpstairs(IsoGameCharacter var1) {
    IsoGridSquare var2 = IsoPlayer.getInstance().getCurrentSquare();
      return var2.getZ() < var1.getCurrentSquare().getZ();
   }

    std::string getSoundToPlay(IsoGameCharacter var1) {
      if (FMODManager.instance.getNumListeners() == 1) {
         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
            if (var3 != nullptr && var3 != var1 && !var3.Traits.Deaf.isSet()) {
               if ((int)var3.getZ() < (int)var1.getZ()) {
                  return this.upstairs;
               }
               break;
            }
         }
      }

    IsoObject var5 = var1.getCurrentSquare().getFloor();
      if (var5 != nullptr && var5.getSprite() != nullptr && var5.getSprite().getName() != nullptr) {
    std::string var6 = var5.getSprite().getName();
         if (var6.startsWith("blends_natural_01")) {
            return this.grass;
         } else if (var6.startsWith("floors_interior_tilesandwood_01_")) {
    int var4 = int.parseInt(var6.replaceFirst("floors_interior_tilesandwood_01_", ""));
            return var4 > 40 && var4 < 48 ? this.wood : this.concrete;
         } else if (var6.startsWith("carpentry_02_")) {
            return this.wood;
         } else {
            return var6.startsWith("floors_interior_carpet_") ? this.wood : this.concrete;
         }
      } else {
         return this.concrete;
      }
   }
}
} // namespace fmod
} // namespace fmod
