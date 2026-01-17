#include "zombie/core/skinnedmodel/advancedanimation/LiveAnimNode.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

protected
LiveAnimNode::LiveAnimNode() {
  // TODO: Implement LiveAnimNode
  return nullptr;
}

LiveAnimNode LiveAnimNode::alloc(AnimLayer animLayer, AnimNode sourceNode,
                                 int layerIdx) {
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

void LiveAnimNode::startTransitionIn(LiveAnimNode transitionFrom,
                                     AnimTransition transitionIn,
                                     AnimationTrack track) {
  // TODO: Implement startTransitionIn
}

void LiveAnimNode::startTransitionIn(AnimNode transitionFrom,
                                     AnimTransition transitionIn,
                                     AnimationTrack track) {
  // TODO: Implement startTransitionIn
}

void LiveAnimNode::setTransitionOut(AnimTransition transitionOut) {
  // TODO: Implement setTransitionOut
}

void LiveAnimNode::update(float timeDelta) {
  // TODO: Implement update
}

void LiveAnimNode::updateTransitioningIn(float float5) {
  // TODO: Implement updateTransitioningIn
}

void LiveAnimNode::addMainTrack(AnimationTrack track) {
  // TODO: Implement addMainTrack
}

void LiveAnimNode::setMainTracksPlaying(bool boolean0) {
  // TODO: Implement setMainTracksPlaying
}

void LiveAnimNode::updateBlendingIn(float float2) {
  // TODO: Implement updateBlendingIn
}

void LiveAnimNode::updateBlendingOut(float float2) {
  // TODO: Implement updateBlendingOut
}

float LiveAnimNode::incrementBlendTime(float float1, float float2,
                                       float float3) {
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

void LiveAnimNode::onAnimStarted(AnimationTrack track) {
  // TODO: Implement onAnimStarted
}

void LiveAnimNode::onLoopedAnim(AnimationTrack track) {
  // TODO: Implement onLoopedAnim
}

void LiveAnimNode::onNonLoopedAnimFadeOut(AnimationTrack track) {
  // TODO: Implement onNonLoopedAnimFadeOut
}

void LiveAnimNode::onNonLoopedAnimFinished(AnimationTrack track) {
  // TODO: Implement onNonLoopedAnimFinished
}

void LiveAnimNode::onTrackDestroyed(AnimationTrack track) {
  // TODO: Implement onTrackDestroyed
}

void LiveAnimNode::invokeAnimStartTimeEvent() {
  // TODO: Implement invokeAnimStartTimeEvent
}

void LiveAnimNode::invokeAnimEndTimeEvent() {
  // TODO: Implement invokeAnimEndTimeEvent
}

void LiveAnimNode::invokeAnimTimeEvent(AnimEvent.AnimEventTime animEventTime) {
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

void LiveAnimNode::setActive(bool active) {
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

AnimationTrack LiveAnimNode::getPlayingTrackAt(int trackIdx) {
  // TODO: Implement getPlayingTrackAt
  return nullptr;
}

std::string LiveAnimNode::getTransitionFrom() {
  // TODO: Implement getTransitionFrom
  return "";
}

void LiveAnimNode::setTransitionInBlendDelta(float blendDelta) {
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

AnimTransition
LiveAnimNode::findTransitionTo(IAnimationVariableSource varSource,
                               const std::string &name) {
  // TODO: Implement findTransitionTo
  return nullptr;
}

float LiveAnimNode::getSpeedScale(IAnimationVariableSource varSource) {
  // TODO: Implement getSpeedScale
  return 0;
}

void LiveAnimNode::reset() {
  // TODO: Implement reset
}

} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
