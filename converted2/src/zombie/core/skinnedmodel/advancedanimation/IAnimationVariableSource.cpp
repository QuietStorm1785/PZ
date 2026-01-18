#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableSource.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

IAnimationVariableSlot
IAnimationVariableSource::getVariable(AnimationVariableHandle handle) {
  // TODO: Implement getVariable
  return nullptr;
}

IAnimationVariableSlot
IAnimationVariableSource::getVariable(const std::string &key) {
  // TODO: Implement getVariable
  return nullptr;
}

std::string
IAnimationVariableSource::getVariableString(const std::string &name) {
  // TODO: Implement getVariableString
  return "";
}

float IAnimationVariableSource::getVariableFloat(const std::string &name,
                                                 float defaultVal) {
  // TODO: Implement getVariableFloat
  return 0;
}

bool IAnimationVariableSource::getVariableBoolean(const std::string &name) {
  // TODO: Implement getVariableBoolean
  return false;
}

bool IAnimationVariableSource::getVariableBoolean(const std::string &key,
                                                  bool defaultVal) {
  // TODO: Implement getVariableBoolean
  return false;
}

bool IAnimationVariableSource::isVariable(const std::string &name,
                                          const std::string &val) {
  // TODO: Implement isVariable
  return false;
}

bool IAnimationVariableSource::containsVariable(const std::string &name) {
  // TODO: Implement containsVariable
  return false;
}

} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
