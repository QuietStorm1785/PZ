#include "zombie/core/skinnedmodel/advancedanimation/AnimLayer.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

public AnimLayer::AnimLayer(IAnimatable character, IAnimEventCallback animEventsCallback) {
 // TODO: Implement AnimLayer
 return nullptr;
}

public AnimLayer::AnimLayer(AnimLayer parentLayer, IAnimatable character, IAnimEventCallback animEventsCallback) {
 // TODO: Implement AnimLayer
 return nullptr;
}

std::string AnimLayer::getCurrentStateName() {
 // TODO: Implement getCurrentStateName
 return "";
}

bool AnimLayer::hasState() {
 // TODO: Implement hasState
 return false;
}

bool AnimLayer::isStateless() {
 // TODO: Implement isStateless
 return false;
}

bool AnimLayer::isSubLayer() {
 // TODO: Implement isSubLayer
 return false;
}

bool AnimLayer::isCurrentState(const std::string& stateName) {
 // TODO: Implement isCurrentState
 return false;
}

AnimationMultiTrack AnimLayer::getAnimationTrack() {
 // TODO: Implement getAnimationTrack
 return nullptr;
}

IAnimationVariableSource AnimLayer::getVariableSource() {
 // TODO: Implement getVariableSource
 return nullptr;
}

LiveAnimNode AnimLayer::getCurrentSyncNode() {
 // TODO: Implement getCurrentSyncNode
 return nullptr;
}

AnimationTrack AnimLayer::getCurrentSyncTrack() {
 // TODO: Implement getCurrentSyncTrack
 return nullptr;
}

void AnimLayer::onAnimStarted(AnimationTrack track) {
 // TODO: Implement onAnimStarted
}

void AnimLayer::onLoopedAnim(AnimationTrack track) {
 // TODO: Implement onLoopedAnim
}

void AnimLayer::onNonLoopedAnimFadeOut(AnimationTrack track) {
 // TODO: Implement onNonLoopedAnimFadeOut
}

void AnimLayer::onNonLoopedAnimFinished(AnimationTrack track) {
 // TODO: Implement onNonLoopedAnimFinished
}

void AnimLayer::onTrackDestroyed(AnimationTrack track) {
 // TODO: Implement onTrackDestroyed
}

void AnimLayer::invokeAnimEvent(AnimationTrack animationTrack, AnimEvent animEvent, bool boolean0) {
 // TODO: Implement invokeAnimEvent
}

void AnimLayer::invokeAnimEvent(AnimEvent animEvent) {
 // TODO: Implement invokeAnimEvent
}

std::string AnimLayer::GetDebugString() {
 // TODO: Implement GetDebugString
 return "";
}

void AnimLayer::Reset() {
 // TODO: Implement Reset
}

bool AnimLayer::TransitionTo(AnimState newState, bool force) {
 // TODO: Implement TransitionTo
 return false;
}

void AnimLayer::Update() {
 // TODO: Implement Update
}

void AnimLayer::updateInternal() {
 // TODO: Implement updateInternal
}

void AnimLayer::updateMaximumTwist(IAnimationVariableSource iAnimationVariableSource) {
 // TODO: Implement updateMaximumTwist
}

void AnimLayer::updateNodeActiveFlags() {
 // TODO: Implement updateNodeActiveFlags
}

void AnimLayer::updateNewNodeTransitions() {
 // TODO: Implement updateNewNodeTransitions
}

void AnimLayer::updateNewNodeTransitionsInternal() {
 // TODO: Implement updateNewNodeTransitionsInternal
}

LiveAnimNode AnimLayer::findTransitionToNewNode(LiveAnimNode newNode, bool isSubNode) {
 // TODO: Implement findTransitionToNewNode
 return nullptr;
}

void AnimLayer::removeFadedOutNodes() {
 // TODO: Implement removeFadedOutNodes
}

void AnimLayer::render() {
 // TODO: Implement render
}

void AnimLayer::logBlendWeights() {
 // TODO: Implement logBlendWeights
}

void AnimLayer::logCurrentState() {
 // TODO: Implement logCurrentState
}

void AnimLayer::removeLiveNodeAt(int int0) {
 // TODO: Implement removeLiveNodeAt
}

void AnimLayer::applyBlendField(LiveAnimNode liveAnimNode, float float0, float float1) {
 // TODO: Implement applyBlendField
}

void AnimLayer::getOrCreateLiveNode(AnimNode animNode) {
 // TODO: Implement getOrCreateLiveNode
}

LiveAnimNode AnimLayer::findLiveNode(AnimNode animNode) {
 // TODO: Implement findLiveNode
 return nullptr;
}

void AnimLayer::startAnimTrack(const std::string& string, LiveAnimNode liveAnimNode) {
 // TODO: Implement startAnimTrack
}

AnimationTrack AnimLayer::startAnimTrack(const std::string& string, AnimLayer.StartAnimTrackParameters startAnimTrackParameters) {
 // TODO: Implement startAnimTrack
 return nullptr;
}

int AnimLayer::getDepth() {
 // TODO: Implement getDepth
 return 0;
}

LiveAnimNode AnimLayer::getHighestLiveNode() {
 // TODO: Implement getHighestLiveNode
 return nullptr;
}

AnimationTrack AnimLayer::findSyncTrack(LiveAnimNode liveAnimNode) {
 // TODO: Implement findSyncTrack
 return nullptr;
}

std::string AnimLayer::getDebugNodeName() {
 // TODO: Implement getDebugNodeName
 return "";
}

bool AnimLayer::isRecording() {
 // TODO: Implement isRecording
 return false;
}

void AnimLayer::reset() {
 // TODO: Implement reset
}

void AnimLayer::onReleased() {
 // TODO: Implement onReleased
}

protected AnimLayer::StartAnimTrackParameters() {
 // TODO: Implement StartAnimTrackParameters
 return nullptr;
}

} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
