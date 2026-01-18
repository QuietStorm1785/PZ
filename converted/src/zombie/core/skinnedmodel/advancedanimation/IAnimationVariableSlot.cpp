#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableSlot.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

std::string IAnimationVariableSlot::getKey() {
 // TODO: Implement getKey
 return "";
}

std::string IAnimationVariableSlot::getValueString() {
 // TODO: Implement getValueString
 return "";
}

float IAnimationVariableSlot::getValueFloat() {
 // TODO: Implement getValueFloat
 return 0;
}

bool IAnimationVariableSlot::getValueBool() {
 // TODO: Implement getValueBool
 return false;
}

void IAnimationVariableSlot::setValue(const std::string& val) {
 // TODO: Implement setValue
}

void IAnimationVariableSlot::setValue(float val) {
 // TODO: Implement setValue
}

void IAnimationVariableSlot::setValue(bool val) {
 // TODO: Implement setValue
}

AnimationVariableType IAnimationVariableSlot::getType() {
 // TODO: Implement getType
 return nullptr;
}

bool IAnimationVariableSlot::canConvertFrom(const std::string& val) {
 // TODO: Implement canConvertFrom
 return false;
}

void IAnimationVariableSlot::clear() {
 // TODO: Implement clear
}

} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
