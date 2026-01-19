#pragma once
#include "zombie/core/math/PZMath.h"
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

class AnimationVariableSlotCallbackInt : public AnimationVariableSlotCallback {
public:
 int m_defaultValue = 0;

public
 AnimationVariableSlotCallbackInt(
 std::string_view string,
 AnimationVariableSlotCallbackInt
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 super(string, callbackGetStrongTyped);
 }

public
 AnimationVariableSlotCallbackInt(
 String string,
 AnimationVariableSlotCallbackInt
 .CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackInt
 .CallbackSetStrongTyped callbackSetStrongTyped) {
 super(string, callbackGetStrongTyped, callbackSetStrongTyped);
 }

public
 AnimationVariableSlotCallbackInt(
 std::string_view string, int int0,
 AnimationVariableSlotCallbackInt
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 super(string, callbackGetStrongTyped);
 this->m_defaultValue = int0;
 }

public
 AnimationVariableSlotCallbackInt(
 String string, int int0,
 AnimationVariableSlotCallbackInt
 .CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackInt
 .CallbackSetStrongTyped callbackSetStrongTyped) {
 super(string, callbackGetStrongTyped, callbackSetStrongTyped);
 this->m_defaultValue = int0;
 }

 int getDefaultValue() { return this->m_defaultValue; }

 std::string getValueString() { return this->getValue().toString(); }

 float getValueFloat() { return this->getValue().intValue(); }

 bool getValueBool() { return this->getValueFloat() != 0.0F; }

 void setValue(std::string_view string) {
 this->trySetValue(PZMath.tryParseInt(string, 0);
 }

 void setValue(float float0) { this->trySetValue((int)float0); }

 void setValue(bool boolean0) { this->trySetValue(boolean0 ? 1 : 0); }

 AnimationVariableType getType() { return AnimationVariableType.Float; }

 bool canConvertFrom(std::string_view var1) { return true; }

public
 interface CallbackGetStrongTyped extends
 AnimationVariableSlotCallback.CallbackGet<Integer> {}

public
 interface CallbackSetStrongTyped extends
 AnimationVariableSlotCallback.CallbackSet<Integer> {}
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
