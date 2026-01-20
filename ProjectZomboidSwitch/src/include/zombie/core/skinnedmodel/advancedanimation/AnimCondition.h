#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/advancedanimation/AnimCondition/1.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimCondition/Type.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimCondition {
public:
    std::string m_Name = "";
    Type m_Type = Type.STRING;
    float m_FloatValue = 0.0F;
    bool m_BoolValue = false;
    std::string m_StringValue = "";
    AnimationVariableHandle m_variableHandle;

    std::string toString() {
      return std::string.format("AnimCondition{name:%s type:%s value:%s }", this.m_Name, this.m_Type, this.getValueString());
   }

    std::string getConditionString() {
      return this.m_Type == Type.OR ? "OR" : std::string.format("( %s %s %s )", this.m_Name, this.m_Type, this.getValueString());
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    std::string getValueString() {
      switch (1.$SwitchMap$zombie$core$skinnedmodel$advancedanimation$AnimCondition$Type[this.m_Type.ordinal()]) {
         case 1:
         case 2:
         case 3:
         case 4:
            return std::string.valueOf(this.m_FloatValue);
         case 5:
            return this.m_BoolValue ? "true" : "false";
         case 6:
         case 7:
            return this.m_StringValue;
         case 8:
            return " -- OR -- ";
         default:
            throw RuntimeException("Unexpected internal type:" + this.m_Type);
      }
   }

    bool check(IAnimationVariableSource var1) {
      return this.checkInternal(var1);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool checkInternal(IAnimationVariableSource var1) {
    Type var2 = this.m_Type;
      if (var2 == Type.OR) {
    return false;
      } else {
         if (this.m_variableHandle == nullptr) {
            this.m_variableHandle = AnimationVariableHandle.alloc(this.m_Name);
         }

    IAnimationVariableSlot var3 = var1.getVariable(this.m_variableHandle);
         switch (1.$SwitchMap$zombie$core$skinnedmodel$advancedanimation$AnimCondition$Type[var2.ordinal()]) {
            case 1:
               return var3 != nullptr && this.m_FloatValue == var3.getValueFloat();
            case 2:
               return var3 != nullptr && this.m_FloatValue != var3.getValueFloat();
            case 3:
               return var3 != nullptr && var3.getValueFloat() < this.m_FloatValue;
            case 4:
               return var3 != nullptr && var3.getValueFloat() > this.m_FloatValue;
            case 5:
               return (var3 != nullptr && var3.getValueBool()) == this.m_BoolValue;
            case 6:
               return this.m_StringValue.equalsIgnoreCase(var3 != nullptr ? var3.getValueString() : "");
            case 7:
               return !this.m_StringValue.equalsIgnoreCase(var3 != nullptr ? var3.getValueString() : "");
            case 8:
    return false;
            default:
               throw RuntimeException("Unexpected internal type:" + this.m_Type);
         }
      }
   }

    static bool pass(IAnimationVariableSource var0, List<AnimCondition> var1) {
    bool var2 = true;

      for (int var3 = 0; var3 < var1.size(); var3++) {
    AnimCondition var4 = (AnimCondition)var1.get(var3);
         if (var4.m_Type == Type.OR) {
            if (var2) {
               break;
            }

            var2 = true;
         } else {
            var2 = var2 && var4.check(var0);
         }
      }

    return var2;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
