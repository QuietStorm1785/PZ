#pragma once
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/core/math/PZMath.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZombieThumpManager : public BaseZombieSoundManager {
public:
  static const ZombieThumpManager instance = new ZombieThumpManager();

public
  ZombieThumpManager() { super(40, 100); }

  void playSound(IsoZombie zombie0) {
    long long0 = 0L;
    if (zombie0.thumpFlag == 1) {
      long0 = zombie0.getEmitter().playSoundImpl("ZombieThumpGeneric", nullptr);
    } else if (zombie0.thumpFlag == 2) {
      zombie0.getEmitter().playSoundImpl("ZombieThumpGeneric", nullptr);
      long0 = zombie0.getEmitter().playSoundImpl("ZombieThumpWindow", nullptr);
    } else if (zombie0.thumpFlag == 3) {
      long0 = zombie0.getEmitter().playSoundImpl("ZombieThumpWindow", nullptr);
    } else if (zombie0.thumpFlag == 4) {
      long0 = zombie0.getEmitter().playSoundImpl("ZombieThumpMetal", nullptr);
    } else if (zombie0.thumpFlag == 5) {
      long0 =
          zombie0.getEmitter().playSoundImpl("ZombieThumpGarageDoor", nullptr);
    }

    FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description =
        FMODManager.instance.getParameterDescription("ObjectCondition");
    zombie0.getEmitter().setParameterValue(
        long0, fmod_studio_parameter_description,
        PZMath.ceil(zombie0.getThumpCondition() * 100.0F));
  }

  void postUpdate() {
    for (int int0 = 0; int0 < this.characters.size(); int0++) {
      this.characters.get(int0).setThumpFlag(0);
    }
  }
}
} // namespace characters
} // namespace zombie
