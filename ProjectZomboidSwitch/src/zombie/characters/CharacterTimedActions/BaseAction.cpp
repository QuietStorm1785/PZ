#include <string>
#include "zombie\characters\CharacterTimedActions/BaseAction.h"

namespace zombie {
namespace characters {
namespace CharacterTimedActions {

public BaseAction::BaseAction(IsoGameCharacter var1) {
    // TODO: Implement BaseAction
    return nullptr;
}

void BaseAction::forceStop() {
    // TODO: Implement forceStop
}

void BaseAction::forceComplete() {
    // TODO: Implement forceComplete
}

void BaseAction::PlayLoopedSoundTillComplete(const std::string& var1, int var2, float var3) {
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

void BaseAction::setUseProgressBar(bool var1) {
    // TODO: Implement setUseProgressBar
}

void BaseAction::setBlockMovementEtc(bool var1) {
    // TODO: Implement setBlockMovementEtc
}

void BaseAction::setOverrideAnimation(bool var1) {
    // TODO: Implement setOverrideAnimation
}

void BaseAction::stopTimedActionAnim() {
    // TODO: Implement stopTimedActionAnim
}

void BaseAction::setAnimVariable(const std::string& var1, const std::string& var2) {
    // TODO: Implement setAnimVariable
}

void BaseAction::setAnimVariable(const std::string& var1, bool var2) {
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

void BaseAction::setActionAnim(CharacterActionAnims var1) {
    // TODO: Implement setActionAnim
}

void BaseAction::setActionAnim(const std::string& var1) {
    // TODO: Implement setActionAnim
}

void BaseAction::setOverrideHandModels(InventoryItem var1, InventoryItem var2) {
    // TODO: Implement setOverrideHandModels
}

void BaseAction::setOverrideHandModels(InventoryItem var1, InventoryItem var2, bool var3) {
    // TODO: Implement setOverrideHandModels
}

void BaseAction::setOverrideHandModelsString(const std::string& var1, const std::string& var2) {
    // TODO: Implement setOverrideHandModelsString
}

void BaseAction::setOverrideHandModelsString(const std::string& var1, const std::string& var2, bool var3) {
    // TODO: Implement setOverrideHandModelsString
}

void BaseAction::setOverrideHandModelsObject(void* var1, void* var2, bool var3) {
    // TODO: Implement setOverrideHandModelsObject
}

void BaseAction::OnAnimEvent(AnimEvent var1) {
    // TODO: Implement OnAnimEvent
}

void BaseAction::setLoopedAction(bool var1) {
    // TODO: Implement setLoopedAction
}

} // namespace CharacterTimedActions
} // namespace characters
} // namespace zombie
