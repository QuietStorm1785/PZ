#pragma once
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

class AnimationVariableSlotCallbackBool : public AnimationVariableSlotCallback {
public:
 bool m_defaultValue = false;

public
 AnimationVariableSlotCallbackBool(
 std::string_view string,
 AnimationVariableSlotCallbackBool
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 super(string, callbackGetStrongTyped);
 }

public
 AnimationVariableSlotCallbackBool(
 String string,
 AnimationVariableSlotCallbackBool
 .CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackBool
 .CallbackSetStrongTyped callbackSetStrongTyped) {
 super(string, callbackGetStrongTyped, callbackSetStrongTyped);
 }

public
 AnimationVariableSlotCallbackBool(
 std::string_view string, bool boolean0,
 AnimationVariableSlotCallbackBool
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 super(string, callbackGetStrongTyped);
 this->m_defaultValue = boolean0;
 }

public
 AnimationVariableSlotCallbackBool(
 String string, boolean boolean0,
 AnimationVariableSlotCallbackBool
 .CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackBool
 .CallbackSetStrongTyped callbackSetStrongTyped) {
 super(string, callbackGetStrongTyped, callbackSetStrongTyped);
 this->m_defaultValue = boolean0;
 }

 bool getDefaultValue() { return this->m_defaultValue; }

 std::string getValueString() { return this->getValue() ? "true" : "false"; }

 float getValueFloat() { return this->getValue() ? 1.0F : 0.0F; }

 bool getValueBool() { return this->getValue(); }

 void setValue(std::string_view string) {
 this->trySetValue(StringUtils.tryParseBoolean(string);
 }

 void setValue(float float0) { this->trySetValue(float0 != 0.0); }

 void setValue(bool boolean0) { this->trySetValue(boolean0); }

 AnimationVariableType getType() { return AnimationVariableType.Boolean; }

 bool canConvertFrom(std::string_view string) {
 return StringUtils.tryParseBoolean(string);
 }

 /**
 * Strong-typed utility type. Useful for auto-typed function overrides, such
 * as
 */
public
 interface CallbackGetStrongTyped extends
 AnimationVariableSlotCallback.CallbackGet<Boolean> {}

public
 interface CallbackSetStrongTyped extends
 AnimationVariableSlotCallback.CallbackSet<Boolean> {}
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
