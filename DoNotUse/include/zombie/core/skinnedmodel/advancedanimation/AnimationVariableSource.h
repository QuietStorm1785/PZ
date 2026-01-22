#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackBool/CallbackGetStrongTyped.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackBool/CallbackSetStrongTyped.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableSource {
public:
   private const Map<std::string, IAnimationVariableSlot> m_GameVariables = new std::map<>(std::string.CASE_INSENSITIVE_ORDER);
   private IAnimationVariableSlot[] m_cachedGameVariableSlots = new IAnimationVariableSlot[0];

    IAnimationVariableSlot getVariable(AnimationVariableHandle var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
    int var2 = var1.getVariableIndex();
         if (var2 < 0) {
    return nullptr;
         } else if (this.m_cachedGameVariableSlots != nullptr && var2 < this.m_cachedGameVariableSlots.length) {
    IAnimationVariableSlot var6 = this.m_cachedGameVariableSlots[var2];
            if (var6 == nullptr) {
               this.m_cachedGameVariableSlots[var2] = this.m_GameVariables.get(var1.getVariableName());
               var6 = this.m_cachedGameVariableSlots[var2];
            }

    return var6;
         } else {
    IAnimationVariableSlot var3 = this.m_GameVariables.get(var1.getVariableName());
            if (var3 == nullptr) {
    return nullptr;
            } else {
               IAnimationVariableSlot[] var4 = new IAnimationVariableSlot[var2 + 1];
               IAnimationVariableSlot[] var5 = this.m_cachedGameVariableSlots;
               if (var5 != nullptr) {
                  this.m_cachedGameVariableSlots = (IAnimationVariableSlot[])PZArrayUtil.arrayCopy(var5, var4, 0, var5.length);
               }

               var4[var2] = var3;
               this.m_cachedGameVariableSlots = var4;
    return var3;
            }
         }
      }
   }

    IAnimationVariableSlot getVariable(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
    return nullptr;
      } else {
    std::string var2 = var1.trim();
         return this.m_GameVariables.get(var2);
      }
   }

    IAnimationVariableSlot getOrCreateVariable(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
    return nullptr;
      } else {
    std::string var2 = var1.trim();
    void* var3 = this.m_GameVariables.get(var2);
         if (var3 == nullptr) {
            var3 = std::make_shared<AnimationVariableGenericSlot>(var2.toLowerCase());
            this.setVariable((IAnimationVariableSlot)var3);
         }

         return (IAnimationVariableSlot)var3;
      }
   }

    void setVariable(IAnimationVariableSlot var1) {
      this.m_GameVariables.put(var1.getKey(), var1);
   }

    void setVariable(const std::string& var1, CallbackGetStrongTyped var2) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackBool>(var1, var2));
   }

    void setVariable(const std::string& var1, CallbackGetStrongTyped var2, CallbackSetStrongTyped var3) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackBool>(var1, var2, var3));
   }

    void setVariable(const std::string& var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var2) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackString>(var1, var2));
   }

   public void setVariable(
      std::string var1,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackSetStrongTyped var3
   ) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackString>(var1, var2, var3));
   }

    void setVariable(const std::string& var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped var2) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackFloat>(var1, var2));
   }

   public void setVariable(
      std::string var1,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackFloat.CallbackSetStrongTyped var3
   ) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackFloat>(var1, var2, var3));
   }

    void setVariable(const std::string& var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var2) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackInt>(var1, var2));
   }

   public void setVariable(
      std::string var1,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackSetStrongTyped var3
   ) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackInt>(var1, var2, var3));
   }

    void setVariable(const std::string& var1, bool var2, CallbackGetStrongTyped var3) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackBool>(var1, var2, var3));
   }

    void setVariable(const std::string& var1, bool var2, CallbackGetStrongTyped var3, CallbackSetStrongTyped var4) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackBool>(var1, var2, var3, var4));
   }

    void setVariable(const std::string& var1, const std::string& var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var3) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackString>(var1, var2, var3));
   }

   public void setVariable(
      std::string var1,
      std::string var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var3,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackSetStrongTyped var4
   ) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackString>(var1, var2, var3, var4));
   }

    void setVariable(const std::string& var1, float var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped var3) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackFloat>(var1, var2, var3));
   }

   public void setVariable(
      std::string var1,
      float var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped var3,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackFloat.CallbackSetStrongTyped var4
   ) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackFloat>(var1, var2, var3, var4));
   }

    void setVariable(const std::string& var1, int var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var3) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackInt>(var1, var2, var3));
   }

   public void setVariable(
      std::string var1,
      int var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var3,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackSetStrongTyped var4
   ) {
      this.setVariable(std::make_shared<AnimationVariableSlotCallbackInt>(var1, var2, var3, var4));
   }

    void setVariable(const std::string& var1, const std::string& var2) {
      this.getOrCreateVariable(var1).setValue(var2);
   }

    void setVariable(const std::string& var1, bool var2) {
      this.getOrCreateVariable(var1).setValue(var2);
   }

    void setVariable(const std::string& var1, float var2) {
      this.getOrCreateVariable(var1).setValue(var2);
   }

    void clearVariable(const std::string& var1) {
    IAnimationVariableSlot var2 = this.getVariable(var1);
      if (var2 != nullptr) {
         var2.clear();
      }
   }

    void clearVariables() {
      for (IAnimationVariableSlot var2 : this.getGameVariables()) {
         var2.clear();
      }
   }

    std::string getVariableString(const std::string& var1) {
    IAnimationVariableSlot var2 = this.getVariable(var1);
      return var2 != nullptr ? var2.getValueString() : "";
   }

    float getVariableFloat(const std::string& var1, float var2) {
    IAnimationVariableSlot var3 = this.getVariable(var1);
      return var3 != nullptr ? var3.getValueFloat() : var2;
   }

    bool getVariableBoolean(const std::string& var1) {
    IAnimationVariableSlot var2 = this.getVariable(var1);
      return var2 != nullptr && var2.getValueBool();
   }

    bool getVariableBoolean(const std::string& var1, bool var2) {
    IAnimationVariableSlot var3 = this.getVariable(var1);
      return var3 != nullptr ? var3.getValueBool() : var2;
   }

   public Iterable<IAnimationVariableSlot> getGameVariables() {
      return this.m_GameVariables.values();
   }

    bool isVariable(const std::string& var1, const std::string& var2) {
      return StringUtils.equalsIgnoreCase(this.getVariableString(var1), var2);
   }

    bool containsVariable(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
    return false;
      } else {
    std::string var2 = var1.trim();
         return this.m_GameVariables.containsKey(var2);
      }
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
