#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMODFootstep {
public:
  std::string wood;
  std::string concrete;
  std::string grass;
  std::string upstairs;
  std::string woodCreak;

public
  FMODFootstep(const std::string &arg0, const std::string &arg1,
               const std::string &arg2, const std::string &arg3) {
    this.grass = arg0;
    this.wood = arg1;
    this.concrete = arg2;
    this.upstairs = arg3;
    this.woodCreak = "HumanFootstepFloorCreaking";
  }

  bool isUpstairs(IsoGameCharacter arg0) {
    IsoGridSquare square = IsoPlayer.getInstance().getCurrentSquare();
    return square.getZ() < arg0.getCurrentSquare().getZ();
  }

  std::string getSoundToPlay(IsoGameCharacter arg0) {
    if (FMODManager.instance.getNumListeners() == 1) {
      for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
        IsoPlayer player = IsoPlayer.players[int0];
        if (player != nullptr && player != arg0 &&
            !player.Traits.Deaf.isSet()) {
          if ((int)player.getZ() < (int)arg0.getZ()) {
            return this.upstairs;
          }
          break;
        }
      }
    }

    IsoObject object = arg0.getCurrentSquare().getFloor();
    if (object != nullptr && object.getSprite() != nullptr &&
        object.getSprite().getName() != nullptr) {
      std::string string = object.getSprite().getName();
      if (string.startsWith("blends_natural_01")) {
        return this.grass;
      } else if (string.startsWith("floors_interior_tilesandwood_01_")) {
        int int1 = Integer.parseInt(
            string.replaceFirst("floors_interior_tilesandwood_01_", ""));
        return int1 > 40 && int1 < 48 ? this.wood : this.concrete;
      } else if (string.startsWith("carpentry_02_")) {
        return this.wood;
      } else {
        return string.startsWith("floors_interior_carpet_") ? this.wood
                                                            : this.concrete;
      }
    } else {
      return this.concrete;
    }
  }
}
} // namespace fmod
} // namespace fmod
