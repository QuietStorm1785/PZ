#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class ZombieFootstepManager : public BaseZombieSoundManager {
public:
    static auto instance = std::make_shared<ZombieFootstepManager>();

    public ZombieFootstepManager() {
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
