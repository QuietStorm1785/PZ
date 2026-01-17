#pragma once
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

class ZombieFootstepManager : public BaseZombieSoundManager {
public:
  static const ZombieFootstepManager instance = new ZombieFootstepManager();

public
  ZombieFootstepManager() { super(40, 500); }

  void playSound(IsoZombie zombie0) {
    zombie0.getEmitter().playFootsteps("ZombieFootstepsCombined",
                                       zombie0.getFootstepVolume());
  }

  void postUpdate() {}
}
} // namespace characters
} // namespace zombie
