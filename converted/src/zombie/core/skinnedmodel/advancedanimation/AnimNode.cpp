#include "zombie/core/skinnedmodel/advancedanimation/AnimNode.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

AnimNode AnimNode::Parse(const std::string &source) {
  // TODO: Implement Parse
  return nullptr;
}

bool AnimNode::checkConditions(IAnimationVariableSource varSource) {
  // TODO: Implement checkConditions
  return false;
}

float AnimNode::getSpeedScale(IAnimationVariableSource varSource) {
  // TODO: Implement getSpeedScale
  return 0;
}

bool AnimNode::isIdleAnim() {
  // TODO: Implement isIdleAnim
  return false;
}

AnimTransition AnimNode::findTransitionTo(IAnimationVariableSource varSource,
                                          const std::string &targetName) {
  // TODO: Implement findTransitionTo
  return nullptr;
}

std::string AnimNode::toString() {
  // TODO: Implement toString
  return "";
}

std::string AnimNode::getConditionsString() {
  // TODO: Implement getConditionsString
  return "";
}

bool AnimNode::isAbstract() {
  // TODO: Implement isAbstract
  return false;
}

float AnimNode::getBlendOutTime() {
  // TODO: Implement getBlendOutTime
  return 0;
}

std::string AnimNode::getDeferredBoneName() {
  // TODO: Implement getDeferredBoneName
  return "";
}

BoneAxis AnimNode::getDeferredBoneAxis() {
  // TODO: Implement getDeferredBoneAxis
  return nullptr;
}

int AnimNode::getPriority() {
  // TODO: Implement getPriority
  return 0;
}

} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
