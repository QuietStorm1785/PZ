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

class AnimationVariableSlotCallbackFloat
    : public AnimationVariableSlotCallback {
public:
  float m_defaultValue = 0.0F;

public
  AnimationVariableSlotCallbackFloat(
      const std::string &string,
      AnimationVariableSlotCallbackFloat
          .CallbackGetStrongTyped callbackGetStrongTyped) {
    super(string, callbackGetStrongTyped);
  }

public
  AnimationVariableSlotCallbackFloat(
      String string,
      AnimationVariableSlotCallbackFloat
          .CallbackGetStrongTyped callbackGetStrongTyped,
      AnimationVariableSlotCallbackFloat
          .CallbackSetStrongTyped callbackSetStrongTyped) {
    super(string, callbackGetStrongTyped, callbackSetStrongTyped);
  }

public
  AnimationVariableSlotCallbackFloat(
      const std::string &string, float float0,
      AnimationVariableSlotCallbackFloat
          .CallbackGetStrongTyped callbackGetStrongTyped) {
    super(string, callbackGetStrongTyped);
    this.m_defaultValue = float0;
  }

public
  AnimationVariableSlotCallbackFloat(
      String string, float float0,
      AnimationVariableSlotCallbackFloat
          .CallbackGetStrongTyped callbackGetStrongTyped,
      AnimationVariableSlotCallbackFloat
          .CallbackSetStrongTyped callbackSetStrongTyped) {
    super(string, callbackGetStrongTyped, callbackSetStrongTyped);
    this.m_defaultValue = float0;
  }

  float getDefaultValue() { return this.m_defaultValue; }

  std::string getValueString() { return this.getValue().toString(); }

  float getValueFloat() { return this.getValue(); }

  bool getValueBool() { return this.getValueFloat() != 0.0F; }

  void setValue(const std::string &string) {
    this.trySetValue(PZMath.tryParseFloat(string, 0.0F));
  }

  void setValue(float float0) { this.trySetValue(float0); }

  void setValue(bool boolean0) { this.trySetValue(boolean0 ? 1.0F : 0.0F); }

  AnimationVariableType getType() { return AnimationVariableType.Float; }

  bool canConvertFrom(const std::string &var1) { return true; }

public
  interface CallbackGetStrongTyped extends
      AnimationVariableSlotCallback.CallbackGet<Float> {}

public
  interface CallbackSetStrongTyped extends
      AnimationVariableSlotCallback.CallbackSet<Float> {}
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
