#pragma once
#include "zombie/core/math/PZMath.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationVariableSlotCallbackString
 : public AnimationVariableSlotCallback {
public:
 std::string m_defaultValue = "";

public
 AnimationVariableSlotCallbackString(
 std::string_view string,
 AnimationVariableSlotCallbackString
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 super(string, callbackGetStrongTyped);
 }

public
 AnimationVariableSlotCallbackString(
 String string,
 AnimationVariableSlotCallbackString
 .CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackString
 .CallbackSetStrongTyped callbackSetStrongTyped) {
 super(string, callbackGetStrongTyped, callbackSetStrongTyped);
 }

public
 AnimationVariableSlotCallbackString(
 String string0, String string1,
 AnimationVariableSlotCallbackString
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 super(string0, callbackGetStrongTyped);
 this->m_defaultValue = string1;
 }

public
 AnimationVariableSlotCallbackString(
 String string0, String string1,
 AnimationVariableSlotCallbackString
 .CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackString
 .CallbackSetStrongTyped callbackSetStrongTyped) {
 super(string0, callbackGetStrongTyped, callbackSetStrongTyped);
 this->m_defaultValue = string1;
 }

 std::string getDefaultValue() { return this->m_defaultValue; }

 std::string getValueString() { return this->getValue(); }

 float getValueFloat() { return PZMath.tryParseFloat(this->getValue(), 0.0F); }

 bool getValueBool() { return StringUtils.tryParseBoolean(this->getValue()); }

 void setValue(std::string_view string) { this->trySetValue(string); }

 void setValue(float float0) { this->trySetValue(String.valueOf(float0); }

 void setValue(bool boolean0) {
 this->trySetValue(boolean0 ? "true" : "false");
 }

 AnimationVariableType getType() { return AnimationVariableType.String; }

 bool canConvertFrom(std::string_view var1) { return true; }

public
 interface CallbackGetStrongTyped extends
 AnimationVariableSlotCallback.CallbackGet<String> {}

public
 interface CallbackSetStrongTyped extends
 AnimationVariableSlotCallback.CallbackSet<String> {}
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
