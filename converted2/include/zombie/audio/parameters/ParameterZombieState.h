#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoZombie.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParameterZombieState : public FMODLocalParameter {
public:
  const IsoZombie zombie;
private
  ParameterZombieState.State state = ParameterZombieState.State.Idle;

public
  ParameterZombieState(IsoZombie _zombie) {
    super("ZombieState");
    this.zombie = _zombie;
  }

  float calculateCurrentValue() {
    if (this.zombie.target == nullptr) {
      if (this.state == ParameterZombieState.State.SearchTarget) {
        this.setState(ParameterZombieState.State.Idle);
      }
    } else if (this.state == ParameterZombieState.State.Idle) {
      this.setState(ParameterZombieState.State.SearchTarget);
    }

    return this.state.index;
  }

  void setState(ParameterZombieState.State _state) {
    if (_state != this.state) {
      this.state = _state;
    }
  }

  bool isState(ParameterZombieState.State _state) {
    return this.state == _state;
  }

public
  static enum State {
    Idle(0), Eating(1), SearchTarget(2), LockTarget(3), AttackScratch(4),
    AttackLacerate(5), AttackBite(6), Hit(7), Death(8), Reanimate(9),
    Pushed(10), GettingUp(11), Attack(12), RunOver(13);

    const int index;

    private State(int int1){this.index = int1;}
}
} // namespace parameters
} // namespace audio
} // namespace zombie
} // namespace zombie
