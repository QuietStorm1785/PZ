#include <string>
#include "zombie\core\skinnedmodel\advancedanimation/LiveAnimNode.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

protected LiveAnimNode::LiveAnimNode() {
    // TODO: Implement LiveAnimNode
    return nullptr;
}

LiveAnimNode LiveAnimNode::alloc(AnimLayer var0, AnimNode var1, int var2) {
    // TODO: Implement alloc
    return nullptr;
}

void LiveAnimNode::reset() {
    // TODO: Implement reset
}

void LiveAnimNode::onReleased() {
    // TODO: Implement onReleased
}

std::string LiveAnimNode::getName() {
    // TODO: Implement getName
    return "";
}

bool LiveAnimNode::isTransitioningIn() {
    // TODO: Implement isTransitioningIn
    return false;
}

void LiveAnimNode::startTransitionIn(LiveAnimNode var1, AnimTransition var2, AnimationTrack var3) {
    // TODO: Implement startTransitionIn
}

void LiveAnimNode::startTransitionIn(AnimNode var1, AnimTransition var2, AnimationTrack var3) {
    // TODO: Implement startTransitionIn
}

void LiveAnimNode::setTransitionOut(AnimTransition var1) {
    // TODO: Implement setTransitionOut
}

void LiveAnimNode::update(float var1) {
    // TODO: Implement update
}

void LiveAnimNode::updateTransitioningIn(float var1) {
    // TODO: Implement updateTransitioningIn
}

void LiveAnimNode::addMainTrack(AnimationTrack var1) {
    // TODO: Implement addMainTrack
}

void LiveAnimNode::setMainTracksPlaying(bool var1) {
    // TODO: Implement setMainTracksPlaying
}

void LiveAnimNode::updateBlendingIn(float var1) {
    // TODO: Implement updateBlendingIn
}

void LiveAnimNode::updateBlendingOut(float var1) {
    // TODO: Implement updateBlendingOut
}

float LiveAnimNode::incrementBlendTime(float var1, float var2, float var3) {
    // TODO: Implement incrementBlendTime
    return 0;
}

float LiveAnimNode::getTransitionInBlendInTime() {
    // TODO: Implement getTransitionInBlendInTime
    return 0;
}

float LiveAnimNode::getMainInitialRewindTime() {
    // TODO: Implement getMainInitialRewindTime
    return 0;
}

float LiveAnimNode::getMaxDuration() {
    // TODO: Implement getMaxDuration
    return 0;
}

float LiveAnimNode::getTransitionInBlendOutTime() {
    // TODO: Implement getTransitionInBlendOutTime
    return 0;
}

float LiveAnimNode::getBlendInTime() {
    // TODO: Implement getBlendInTime
    return 0;
}

float LiveAnimNode::getBlendOutTime() {
    // TODO: Implement getBlendOutTime
    return 0;
}

void LiveAnimNode::onAnimStarted(AnimationTrack var1) {
    // TODO: Implement onAnimStarted
}

void LiveAnimNode::onLoopedAnim(AnimationTrack var1) {
    // TODO: Implement onLoopedAnim
}

void LiveAnimNode::onNonLoopedAnimFadeOut(AnimationTrack var1) {
    // TODO: Implement onNonLoopedAnimFadeOut
}

void LiveAnimNode::onNonLoopedAnimFinished(AnimationTrack var1) {
    // TODO: Implement onNonLoopedAnimFinished
}

void LiveAnimNode::onTrackDestroyed(AnimationTrack var1) {
    // TODO: Implement onTrackDestroyed
}

void LiveAnimNode::invokeAnimStartTimeEvent() {
    // TODO: Implement invokeAnimStartTimeEvent
}

void LiveAnimNode::invokeAnimEndTimeEvent() {
    // TODO: Implement invokeAnimEndTimeEvent
}

void LiveAnimNode::invokeAnimTimeEvent(AnimEventTime var1) {
    // TODO: Implement invokeAnimTimeEvent
}

AnimNode LiveAnimNode::getSourceNode() {
    // TODO: Implement getSourceNode
    return nullptr;
}

bool LiveAnimNode::isIdleAnimActive() {
    // TODO: Implement isIdleAnimActive
    return false;
}

bool LiveAnimNode::isActive() {
    // TODO: Implement isActive
    return false;
}

void LiveAnimNode::setActive(bool var1) {
    // TODO: Implement setActive
}

bool LiveAnimNode::isLooped() {
    // TODO: Implement isLooped
    return false;
}

float LiveAnimNode::getWeight() {
    // TODO: Implement getWeight
    return 0;
}

float LiveAnimNode::getTransitionInWeight() {
    // TODO: Implement getTransitionInWeight
    return 0;
}

bool LiveAnimNode::wasActivated() {
    // TODO: Implement wasActivated
    return false;
}

bool LiveAnimNode::wasDeactivated() {
    // TODO: Implement wasDeactivated
    return false;
}

bool LiveAnimNode::isNew() {
    // TODO: Implement isNew
    return false;
}

int LiveAnimNode::getPlayingTrackCount() {
    // TODO: Implement getPlayingTrackCount
    return 0;
}

bool LiveAnimNode::isMainAnimActive() {
    // TODO: Implement isMainAnimActive
    return false;
}

AnimationTrack LiveAnimNode::getPlayingTrackAt(int var1) {
    // TODO: Implement getPlayingTrackAt
    return nullptr;
}

std::string LiveAnimNode::getTransitionFrom() {
    // TODO: Implement getTransitionFrom
    return "";
}

void LiveAnimNode::setTransitionInBlendDelta(float var1) {
    // TODO: Implement setTransitionInBlendDelta
}

AnimationTrack LiveAnimNode::getTransitionInTrack() {
    // TODO: Implement getTransitionInTrack
    return nullptr;
}

int LiveAnimNode::getTransitionLayerIdx() {
    // TODO: Implement getTransitionLayerIdx
    return 0;
}

int LiveAnimNode::getLayerIdx() {
    // TODO: Implement getLayerIdx
    return 0;
}

int LiveAnimNode::getPriority() {
    // TODO: Implement getPriority
    return 0;
}

std::string LiveAnimNode::getDeferredBoneName() {
    // TODO: Implement getDeferredBoneName
    return "";
}

BoneAxis LiveAnimNode::getDeferredBoneAxis() {
    // TODO: Implement getDeferredBoneAxis
    return nullptr;
}

AnimTransition LiveAnimNode::findTransitionTo(IAnimationVariableSource var1, const std::string& var2) {
    // TODO: Implement findTransitionTo
    return nullptr;
}

float LiveAnimNode::getSpeedScale(IAnimationVariableSource var1) {
    // TODO: Implement getSpeedScale
    return 0;
}

} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
