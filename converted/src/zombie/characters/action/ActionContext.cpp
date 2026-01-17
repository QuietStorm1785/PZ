#include "zombie/characters/action/ActionContext.h"

namespace zombie {
namespace characters {
namespace action {

public
ActionContext::ActionContext(IAnimatable owner) {
  // TODO: Implement ActionContext
  return nullptr;
}

IAnimatable ActionContext::getOwner() {
  // TODO: Implement getOwner
  return nullptr;
}

void ActionContext::update() {
  // TODO: Implement update
}

void ActionContext::updateInternal() {
  // TODO: Implement updateInternal
}

ActionState ActionContext::getNextState() {
  // TODO: Implement getNextState
  return nullptr;
}

void ActionContext::evaluateCurrentStateTransitions() {
  // TODO: Implement evaluateCurrentStateTransitions
}

void ActionContext::evaluateSubStateTransitions() {
  // TODO: Implement evaluateSubStateTransitions
}

bool ActionContext::currentStateSupportsChildState(ActionState actionState) {
  // TODO: Implement currentStateSupportsChildState
  return false;
}

bool ActionContext::hasChildState(ActionState actionState) {
  // TODO: Implement hasChildState
  return false;
}

void ActionContext::setPlaybackStateSnapshot(ActionStateSnapshot snapshot) {
  // TODO: Implement setPlaybackStateSnapshot
}

ActionStateSnapshot ActionContext::getPlaybackStateSnapshot() {
  // TODO: Implement getPlaybackStateSnapshot
  return nullptr;
}

bool ActionContext::setCurrentState(ActionState actionState0) {
  // TODO: Implement setCurrentState
  return false;
}

bool ActionContext::tryAddChildState(ActionState actionState) {
  // TODO: Implement tryAddChildState
  return false;
}

void ActionContext::removeChildStateAt(int int0) {
  // TODO: Implement removeChildStateAt
}

void ActionContext::onStatesChanged() {
  // TODO: Implement onStatesChanged
}

void ActionContext::logCurrentState() {
  // TODO: Implement logCurrentState
}

void ActionContext::invokeAnyStateChangedEvents() {
  // TODO: Implement invokeAnyStateChangedEvents
}

ActionState ActionContext::getCurrentState() {
  // TODO: Implement getCurrentState
  return nullptr;
}

void ActionContext::setGroup(ActionGroup group) {
  // TODO: Implement setGroup
}

ActionGroup ActionContext::getGroup() {
  // TODO: Implement getGroup
  return nullptr;
}

void ActionContext::reportEvent(const std::string &event) {
  // TODO: Implement reportEvent
}

void ActionContext::reportEvent(int animLayer, const std::string &event) {
  // TODO: Implement reportEvent
}

bool ActionContext::hasChildStates() {
  // TODO: Implement hasChildStates
  return false;
}

int ActionContext::childStateCount() {
  // TODO: Implement childStateCount
  return 0;
}

void ActionContext::foreachChildState(Consumer<ActionState> consumer) {
  // TODO: Implement foreachChildState
}

int ActionContext::indexOfChildState(Predicate<ActionState> predicate) {
  // TODO: Implement indexOfChildState
  return 0;
}

ActionState ActionContext::getChildStateAt(int idx) {
  // TODO: Implement getChildStateAt
  return nullptr;
}

std::string ActionContext::getCurrentStateName() {
  // TODO: Implement getCurrentStateName
  return "";
}

std::string ActionContext::getPreviousStateName() {
  // TODO: Implement getPreviousStateName
  return "";
}

bool ActionContext::hasEventOccurred(const std::string &eventName) {
  // TODO: Implement hasEventOccurred
  return false;
}

bool ActionContext::hasEventOccurred(const std::string &eventName,
                                     int layerIdx) {
  // TODO: Implement hasEventOccurred
  return false;
}

void ActionContext::clearEvent(const std::string &eventName) {
  // TODO: Implement clearEvent
}

} // namespace action
} // namespace characters
} // namespace zombie
