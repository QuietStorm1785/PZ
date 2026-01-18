#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimationVariableSlotString : public AnimationVariableSlot {
public:
 std::string m_value;

 public AnimationVariableSlotString(const std::string& string) {
 super(string);
 }

 std::string getValueString() {
 return this->m_value;
 }

 float getValueFloat() {
 return PZMath.tryParseFloat(this->m_value, 0.0F);
 }

 bool getValueBool() {
 return StringUtils.tryParseBoolean(this->m_value);
 }

 void setValue(const std::string& string) {
 this->m_value = string;
 }

 void setValue(float float0) {
 this->m_value = String.valueOf(float0);
 }

 void setValue(bool boolean0) {
 this->m_value = boolean0 ? "true" : "false";
 }

 AnimationVariableType getType() {
 return AnimationVariableType.String;
 }

 bool canConvertFrom(const std::string& var1) {
 return true;
 }

 void clear() {
 this->m_value = "";
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
