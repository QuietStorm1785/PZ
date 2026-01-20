#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackFloat/CallbackGetStrongTyped.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackFloat/CallbackSetStrongTyped.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableSlotCallbackFloat : public AnimationVariableSlotCallback {
public:
    float m_defaultValue = 0.0F;

    public AnimationVariableSlotCallbackFloat(const std::string& var1, CallbackGetStrongTyped var2) {
      super(var1, var2);
   }

    public AnimationVariableSlotCallbackFloat(const std::string& var1, CallbackGetStrongTyped var2, CallbackSetStrongTyped var3) {
      super(var1, var2, var3);
   }

    public AnimationVariableSlotCallbackFloat(const std::string& var1, float var2, CallbackGetStrongTyped var3) {
      super(var1, var3);
      this.m_defaultValue = var2;
   }

    public AnimationVariableSlotCallbackFloat(const std::string& var1, float var2, CallbackGetStrongTyped var3, CallbackSetStrongTyped var4) {
      super(var1, var3, var4);
      this.m_defaultValue = var2;
   }

    float getDefaultValue() {
      return this.m_defaultValue;
   }

    std::string getValueString() {
      return ((float)this.getValue());
   }

    float getValueFloat() {
      return (float)this.getValue();
   }

    bool getValueBool() {
      return this.getValueFloat() != 0.0F;
   }

    void setValue(const std::string& var1) {
      this.trySetValue(PZMath.tryParseFloat(var1, 0.0F));
   }

    void setValue(float var1) {
      this.trySetValue(var1);
   }

    void setValue(bool var1) {
      this.trySetValue(var1 ? 1.0F : 0.0F);
   }

    AnimationVariableType getType() {
      return AnimationVariableType.float;
   }

    bool canConvertFrom(const std::string& var1) {
    return true;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
