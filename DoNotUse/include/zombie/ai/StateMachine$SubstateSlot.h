#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ai {

class StateMachine {
public:
    State state;
    bool shouldBeActive;

   StateMachine$SubstateSlot(State var1) {
      this.state = var1;
      this.shouldBeActive = true;
   }

    State getState() {
      return this.state;
   }

    void setState(State var1) {
      this.state = var1;
   }

    bool isEmpty() {
      return this.state == nullptr;
   }
}
} // namespace ai
} // namespace zombie
