#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimationVariableSlotBool : public AnimationVariableSlot {
public:
 bool m_value;

 public AnimationVariableSlotBool(const std::string& string) {
 super(string);
 }

 std::string getValueString() {
 return this->m_value ? "true" : "false";
 }

 float getValueFloat() {
 return this->m_value ? 1.0F : 0.0F;
 }

 bool getValueBool() {
 return this->m_value;
 }

 void setValue(const std::string& string) {
 this->m_value = StringUtils.tryParseBoolean(string);
 }

 void setValue(float float0) {
 this->m_value = float0 != 0.0;
 }

 void setValue(bool boolean0) {
 this->m_value = boolean0;
 }

 AnimationVariableType getType() {
 return AnimationVariableType.Boolean;
 }

 bool canConvertFrom(const std::string& string) {
 return StringUtils.isBoolean(string);
 }

 void clear() {
 this->m_value = false;
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
