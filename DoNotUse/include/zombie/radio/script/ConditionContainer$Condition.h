#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/globals/CompareMethod.h"
#include "zombie/radio/globals/CompareResult.h"
#include "zombie/radio/globals/RadioGlobal.h"

namespace zombie {
namespace radio {
namespace script {


class ConditionContainer {
public:
    OperatorType operatorType = OperatorType.NONE;
    CompareMethod compareMethod;
    RadioGlobal valueA;
    RadioGlobal valueB;

   public ConditionContainer$Condition(RadioGlobal var1, RadioGlobal var2, CompareMethod var3) {
      this(var1, var2, var3, OperatorType.NONE);
   }

   public ConditionContainer$Condition(RadioGlobal var1, RadioGlobal var2, CompareMethod var3, OperatorType var4) {
      this.valueA = var1;
      this.valueB = var2;
      this.operatorType = var4;
      this.compareMethod = var3;
   }

    CompareResult Evaluate() {
      return this.valueA != nullptr && this.valueB != nullptr ? this.valueA.compare(this.valueB, this.compareMethod) : CompareResult.Invalid;
   }

    OperatorType getNextOperator() {
      return this.operatorType;
   }

    void setNextOperator(OperatorType var1) {
      this.operatorType = var1;
   }
}
} // namespace script
} // namespace radio
} // namespace zombie
