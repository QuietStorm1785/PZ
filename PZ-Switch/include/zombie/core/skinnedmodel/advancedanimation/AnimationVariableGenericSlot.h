#pragma once
#include "zombie/debug/DebugLog.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationVariableGenericSlot : public AnimationVariableSlot {
public:
 AnimationVariableType m_type = AnimationVariableType.Void;
 IAnimationVariableSlot m_valueSlot;

public
 AnimationVariableGenericSlot(const std::string &string) { super(string); }

 std::string getValueString() {
 return this->m_valueSlot != nullptr ? this->m_valueSlot.getValueString()
 : nullptr;
 }

 float getValueFloat() {
 return this->m_valueSlot != nullptr ? this->m_valueSlot.getValueFloat()
 : 0.0F;
 }

 bool getValueBool() {
 return this->m_valueSlot != nullptr && this->m_valueSlot.getValueBool();
 }

 void setValue(const std::string &string) {
 if (this->m_valueSlot.empty() ||
 !this->m_valueSlot.canConvertFrom(string) {
 this->m_valueSlot = new AnimationVariableSlotString(this->getKey());
 this->setType(this->m_valueSlot.getType());
 }

 this->m_valueSlot.setValue(string);
 }

 void setValue(float float0) {
 if (this->m_valueSlot.empty() ||
 this->m_type != AnimationVariableType.Float) {
 this->m_valueSlot = new AnimationVariableSlotFloat(this->getKey());
 this->setType(this->m_valueSlot.getType());
 }

 this->m_valueSlot.setValue(float0);
 }

 void setValue(bool boolean0) {
 if (this->m_valueSlot.empty() ||
 this->m_type != AnimationVariableType.Boolean) {
 this->m_valueSlot = new AnimationVariableSlotBool(this->getKey());
 this->setType(this->m_valueSlot.getType());
 }

 this->m_valueSlot.setValue(boolean0);
 }

 AnimationVariableType getType() { return this->m_type; }

 void setType(AnimationVariableType animationVariableType) {
 if (this->m_type != animationVariableType) {
 if (this->m_type != AnimationVariableType.Void) {
 DebugLog.General.printf("Variable %s converting from %s to %s\n",
 this->getKey(), this->m_type,
 animationVariableType);
 }

 this->m_type = animationVariableType;
 }
 }

 bool canConvertFrom(const std::string &var1) { return true; }

 void clear() {
 this->m_type = AnimationVariableType.Void;
 this->m_valueSlot = nullptr;
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
