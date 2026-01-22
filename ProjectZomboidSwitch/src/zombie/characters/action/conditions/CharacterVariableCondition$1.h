#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/action/conditions/CharacterVariableCondition/Operator.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {


// $VF: synthetic class
class CharacterVariableCondition {
public:
   static {
      try {
         $SwitchMap$zombie$characters$action$conditions$CharacterVariableCondition$Operator[Operator.Equal.ordinal()] = 1;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$characters$action$conditions$CharacterVariableCondition$Operator[Operator.NotEqual.ordinal()] = 2;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$characters$action$conditions$CharacterVariableCondition$Operator[Operator.Less.ordinal()] = 3;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$characters$action$conditions$CharacterVariableCondition$Operator[Operator.LessEqual.ordinal()] = 4;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$characters$action$conditions$CharacterVariableCondition$Operator[Operator.Greater.ordinal()] = 5;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$characters$action$conditions$CharacterVariableCondition$Operator[Operator.GreaterEqual.ordinal()] = 6;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
