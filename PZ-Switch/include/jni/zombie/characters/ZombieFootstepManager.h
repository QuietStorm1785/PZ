#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class ZombieFootstepManager :  BaseZombieSoundManager {
:
    static const ZombieFootstepManager instance = new ZombieFootstepManager();

     ZombieFootstepManager() {
      super(40, 500);
   }

    void playSound(IsoZombie var1) {
      var1.getEmitter().playFootsteps("ZombieFootstepsCombined", var1.getFootstepVolume());
   }

    void postUpdate() {
   }
}
} // namespace characters
} // namespace zombie
