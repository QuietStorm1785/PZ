#include "zombie/ai/StateMachine.h"

namespace zombie {
namespace ai {

public
StateMachine::StateMachine(IsoGameCharacter owner) {
  // TODO: Implement StateMachine
  return nullptr;
}

void StateMachine::changeState(State newState, Iterable<State> subStates) {
  // TODO: Implement changeState
}

void StateMachine::changeState(State newState, Iterable<State> subStates,
                               bool restart) {
  // TODO: Implement changeState
}

void StateMachine::changeRootState(State state0, bool boolean0) {
  // TODO: Implement changeRootState
}

void StateMachine::ensureSubstateActive(State state) {
  // TODO: Implement ensureSubstateActive
}

void StateMachine::removeSubstate(State state) {
  // TODO: Implement removeSubstate
}

void StateMachine::removeSubstate(StateMachine.SubstateSlot substateSlot) {
  // TODO: Implement removeSubstate
}

bool StateMachine::isSubstate(State substate) {
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

State StateMachine::getSubStateAt(int idx) {
  // TODO: Implement getSubStateAt
  return nullptr;
}

void StateMachine::revertToPreviousState(State sender) {
  // TODO: Implement revertToPreviousState
}

void StateMachine::update() {
  // TODO: Implement update
}

void StateMachine::logCurrentState() {
  // TODO: Implement logCurrentState
}

void StateMachine::stateEnter(State state) {
  // TODO: Implement stateEnter
}

void StateMachine::stateExit(State state) {
  // TODO: Implement stateExit
}

void StateMachine::stateAnimEvent(int stateLayer, AnimEvent event) {
  // TODO: Implement stateAnimEvent
}

bool StateMachine::isLocked() {
  // TODO: Implement isLocked
  return false;
}

void StateMachine::setLocked(bool lock) {
  // TODO: Implement setLocked
}

State StateMachine::getState() {
  // TODO: Implement getState
  return nullptr;
}

void StateMachine::setState(State statex) {
  // TODO: Implement setState
}

bool StateMachine::isEmpty() {
  // TODO: Implement isEmpty
  return false;
}

} // namespace ai
} // namespace zombie
