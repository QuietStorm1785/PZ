#include "zombie\ai/StateMachine.h"

namespace zombie {
namespace ai {

public StateMachine::StateMachine(IsoGameCharacter var1) {
    // TODO: Implement StateMachine
    return nullptr;
}

void StateMachine::changeState(State var1, Iterable<State> var2) {
    // TODO: Implement changeState
}

void StateMachine::changeState(State var1, Iterable<State> var2, bool var3) {
    // TODO: Implement changeState
}

void StateMachine::changeRootState(State var1, bool var2) {
    // TODO: Implement changeRootState
}

void StateMachine::ensureSubstateActive(State var1) {
    // TODO: Implement ensureSubstateActive
}

SubstateSlot StateMachine::getExistingSlot(State var1) {
    // TODO: Implement getExistingSlot
    return nullptr;
}

void StateMachine::removeSubstate(State var1) {
    // TODO: Implement removeSubstate
}

void StateMachine::removeSubstate(SubstateSlot var1) {
    // TODO: Implement removeSubstate
}

bool StateMachine::isSubstate(State var1) {
    // TODO: Implement isSubstate
    return false;
}

State StateMachine::getCurrent() {
    // TODO: Implement getCurrent
    return nullptr;
}

State StateMachine::getPrevious() {
    // TODO: Implement getPrevious
    return nullptr;
}

int StateMachine::getSubStateCount() {
    // TODO: Implement getSubStateCount
    return 0;
}

State StateMachine::getSubStateAt(int var1) {
    // TODO: Implement getSubStateAt
    return nullptr;
}

void StateMachine::revertToPreviousState(State var1) {
    // TODO: Implement revertToPreviousState
}

void StateMachine::update() {
    // TODO: Implement update
}

void StateMachine::logCurrentState() {
    // TODO: Implement logCurrentState
}

void StateMachine::stateEnter(State var1) {
    // TODO: Implement stateEnter
}

void StateMachine::stateExit(State var1) {
    // TODO: Implement stateExit
}

void StateMachine::stateAnimEvent(int var1, AnimEvent var2) {
    // TODO: Implement stateAnimEvent
}

bool StateMachine::isLocked() {
    // TODO: Implement isLocked
    return false;
}

void StateMachine::setLocked(bool var1) {
    // TODO: Implement setLocked
}

} // namespace ai
} // namespace zombie
