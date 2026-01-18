#include "zombie/characters/CharacterTimedActions/BaseAction.h"

namespace zombie {
namespace characters {
namespace CharacterTimedActions {

public
BaseAction::BaseAction(IsoGameCharacter _chr) {
  // TODO: Implement BaseAction
  return nullptr;
}

void BaseAction::forceStop() {
  // TODO: Implement forceStop
}

void BaseAction::forceComplete() {
  // TODO: Implement forceComplete
}

void BaseAction::PlayLoopedSoundTillComplete(const std::string &name,
                                             int radius, float maxGain) {
  // TODO: Implement PlayLoopedSoundTillComplete
}

bool BaseAction::hasStalled() {
  // TODO: Implement hasStalled
  return false;
}

float BaseAction::getJobDelta() {
  // TODO: Implement getJobDelta
  return 0;
}

void BaseAction::resetJobDelta() {
  // TODO: Implement resetJobDelta
}

void BaseAction::waitToStart() {
  // TODO: Implement waitToStart
}

void BaseAction::update() {
  // TODO: Implement update
}

void BaseAction::start() {
  // TODO: Implement start
}

void BaseAction::reset() {
  // TODO: Implement reset
}

float BaseAction::getCurrentTime() {
  // TODO: Implement getCurrentTime
  return 0;
}

void BaseAction::stop() {
  // TODO: Implement stop
}

bool BaseAction::valid() {
  // TODO: Implement valid
  return false;
}

bool BaseAction::finished() {
  // TODO: Implement finished
  return false;
}

void BaseAction::perform() {
  // TODO: Implement perform
}

void BaseAction::setUseProgressBar(bool use) {
  // TODO: Implement setUseProgressBar
}

void BaseAction::setBlockMovementEtc(bool block) {
  // TODO: Implement setBlockMovementEtc
}

void BaseAction::setOverrideAnimation(bool override) {
  // TODO: Implement setOverrideAnimation
}

void BaseAction::stopTimedActionAnim() {
  // TODO: Implement stopTimedActionAnim
}

void BaseAction::setAnimVariable(const std::string &key,
                                 const std::string &val) {
  // TODO: Implement setAnimVariable
}

void BaseAction::setAnimVariable(const std::string &key, bool val) {
  // TODO: Implement setAnimVariable
}

std::string BaseAction::getPrimaryHandMdl() {
  // TODO: Implement getPrimaryHandMdl
  return "";
}

std::string BaseAction::getSecondaryHandMdl() {
  // TODO: Implement getSecondaryHandMdl
  return "";
}

InventoryItem BaseAction::getPrimaryHandItem() {
  // TODO: Implement getPrimaryHandItem
  return nullptr;
}

InventoryItem BaseAction::getSecondaryHandItem() {
  // TODO: Implement getSecondaryHandItem
  return nullptr;
}

void BaseAction::setActionAnim(CharacterActionAnims act) {
  // TODO: Implement setActionAnim
}

void BaseAction::setActionAnim(const std::string &animNode) {
  // TODO: Implement setActionAnim
}

void BaseAction::setOverrideHandModels(InventoryItem primaryHand,
                                       InventoryItem secondaryHand) {
  // TODO: Implement setOverrideHandModels
}

void BaseAction::setOverrideHandModels(InventoryItem primaryHand,
                                       InventoryItem secondaryHand,
                                       bool resetModel) {
  // TODO: Implement setOverrideHandModels
}

void BaseAction::setOverrideHandModelsString(const std::string &primaryHand,
                                             const std::string &secondaryHand) {
  // TODO: Implement setOverrideHandModelsString
}

void BaseAction::setOverrideHandModelsString(const std::string &primaryHand,
                                             const std::string &secondaryHand,
                                             bool resetModel) {
  // TODO: Implement setOverrideHandModelsString
}

void BaseAction::setOverrideHandModelsObject(void *primaryHand,
                                             void *secondaryHand,
                                             bool resetModel) {
  // TODO: Implement setOverrideHandModelsObject
}

void BaseAction::OnAnimEvent(AnimEvent event) {
  // TODO: Implement OnAnimEvent
}

void BaseAction::setLoopedAction(bool looped) {
  // TODO: Implement setLoopedAction
}

} // namespace CharacterTimedActions
} // namespace characters
} // namespace zombie
