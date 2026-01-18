#pragma once
#include "zombie/core/math/PZMath.h"
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

class AnimationVariableSlotFloat : public AnimationVariableSlot {
public:
 float m_value = 0.0F;

public
 AnimationVariableSlotFloat(const std::string &string) { super(string); }

 std::string getValueString() { return String.valueOf(this->m_value); }

 float getValueFloat() { return this->m_value; }

 bool getValueBool() { return this->m_value != 0.0F; }

 void setValue(const std::string &string) {
 this->m_value = PZMath.tryParseFloat(string, 0.0F);
 }

 void setValue(float float0) { this->m_value = float0; }

 void setValue(bool boolean0) { this->m_value = boolean0 ? 1.0F : 0.0F; }

 AnimationVariableType getType() { return AnimationVariableType.Float; }

 bool canConvertFrom(const std::string &string) {
 return PZMath.canParseFloat(string);
 }

 void clear() { this->m_value = 0.0F; }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
