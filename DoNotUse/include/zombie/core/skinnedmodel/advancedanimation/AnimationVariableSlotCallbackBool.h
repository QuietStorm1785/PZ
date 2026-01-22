#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackBool/CallbackGetStrongTyped.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackBool/CallbackSetStrongTyped.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableSlotCallbackBool : public AnimationVariableSlotCallback {
public:
    bool m_defaultValue = false;

    public AnimationVariableSlotCallbackBool(const std::string& var1, CallbackGetStrongTyped var2) {
      super(var1, var2);
   }

    public AnimationVariableSlotCallbackBool(const std::string& var1, CallbackGetStrongTyped var2, CallbackSetStrongTyped var3) {
      super(var1, var2, var3);
   }

    public AnimationVariableSlotCallbackBool(const std::string& var1, bool var2, CallbackGetStrongTyped var3) {
      super(var1, var3);
      this.m_defaultValue = var2;
   }

    public AnimationVariableSlotCallbackBool(const std::string& var1, bool var2, CallbackGetStrongTyped var3, CallbackSetStrongTyped var4) {
      super(var1, var3, var4);
      this.m_defaultValue = var2;
   }

    bool getDefaultValue() {
      return this.m_defaultValue;
   }

    std::string getValueString() {
      return this.getValue() ? "true" : "false";
   }

    float getValueFloat() {
      return this.getValue() ? 1.0F : 0.0F;
   }

    bool getValueBool() {
      return (bool)this.getValue();
   }

    void setValue(const std::string& var1) {
      this.trySetValue(StringUtils.tryParseBoolean(var1));
   }

    void setValue(float var1) {
      this.trySetValue(var1 != 0.0);
   }

    void setValue(bool var1) {
      this.trySetValue(var1);
   }

    AnimationVariableType getType() {
      return AnimationVariableType.bool;
   }

    bool canConvertFrom(const std::string& var1) {
      return StringUtils.tryParseBoolean(var1);
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
