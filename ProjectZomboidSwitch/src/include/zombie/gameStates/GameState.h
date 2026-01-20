#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/gameStates/GameStateMachine/StateAction.h"

namespace zombie {
namespace gameStates {


class GameState {
public:
    void enter() {
   }

    void exit() {
   }

    void render() {
   }

    GameState redirectState() {
    return nullptr;
   }

    StateAction update() {
      return StateAction.Continue;
   }

    void yield() {
   }

    void reenter() {
   }
}
} // namespace gameStates
} // namespace zombie
