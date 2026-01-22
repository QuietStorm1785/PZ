#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace audio {
namespace parameters {

enum class ParameterZombieState {
   Idle(0),
   Eating(1),
   SearchTarget(2),
   LockTarget(3),
   AttackScratch(4),
   AttackLacerate(5),
   AttackBite(6),
   Hit(7),
   Death(8),
   Reanimate(9),
   Pushed(10),
   GettingUp(11),
   Attack(12),
   RunOver(13);

    const int index;

   private ParameterZombieState$State(int var3) {
      this.index = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
