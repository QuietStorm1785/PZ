#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackString/CallbackGetStrongTyped.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackString/CallbackSetStrongTyped.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableSlotCallbackString : public AnimationVariableSlotCallback {
public:
    std::string m_defaultValue = "";

    public AnimationVariableSlotCallbackString(const std::string& var1, CallbackGetStrongTyped var2) {
      super(var1, var2);
   }

    public AnimationVariableSlotCallbackString(const std::string& var1, CallbackGetStrongTyped var2, CallbackSetStrongTyped var3) {
      super(var1, var2, var3);
   }

    public AnimationVariableSlotCallbackString(const std::string& var1, const std::string& var2, CallbackGetStrongTyped var3) {
      super(var1, var3);
      this.m_defaultValue = var2;
   }

    public AnimationVariableSlotCallbackString(const std::string& var1, const std::string& var2, CallbackGetStrongTyped var3, CallbackSetStrongTyped var4) {
      super(var1, var3, var4);
      this.m_defaultValue = var2;
   }

    std::string getDefaultValue() {
      return this.m_defaultValue;
   }

    std::string getValueString() {
      return (std::string)this.getValue();
   }

    float getValueFloat() {
      return PZMath.tryParseFloat((std::string)this.getValue(), 0.0F);
   }

    bool getValueBool() {
      return StringUtils.tryParseBoolean((std::string)this.getValue());
   }

    void setValue(const std::string& var1) {
      this.trySetValue(var1);
   }

    void setValue(float var1) {
      this.trySetValue(std::string.valueOf(var1));
   }

    void setValue(bool var1) {
      this.trySetValue(var1 ? "true" : "false");
   }

    AnimationVariableType getType() {
      return AnimationVariableType.std::string;
   }

    bool canConvertFrom(const std::string& var1) {
    return true;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
