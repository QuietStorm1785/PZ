#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/audio/parameters/ParameterZombieState/State.h"
#include "zombie/characters/IsoZombie.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterZombieState : public FMODLocalParameter {
public:
    const IsoZombie zombie;
    State state = State.Idle;

    public ParameterZombieState(IsoZombie var1) {
      super("ZombieState");
      this.zombie = var1;
   }

    float calculateCurrentValue() {
      if (this.zombie.target == nullptr) {
         if (this.state == State.SearchTarget) {
            this.setState(State.Idle);
         }
      } else if (this.state == State.Idle) {
         this.setState(State.SearchTarget);
      }

      return this.state.index;
   }

    void setState(State var1) {
      if (var1 != this.state) {
         this.state = var1;
      }
   }

    bool isState(State var1) {
      return this.state == var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
