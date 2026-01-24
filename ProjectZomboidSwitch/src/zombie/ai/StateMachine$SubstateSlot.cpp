#include "zombie/ai/StateMachine$SubstateSlot.h"

namespace zombie {
namespace ai {

State StateMachine$SubstateSlot::getState() {
    return state;
}

void StateMachine$SubstateSlot::setState(State var1) {
    state = var1;
}

bool StateMachine$SubstateSlot::isEmpty() {
    return state == nullptr;
}

} // namespace ai
} // namespace zombie
