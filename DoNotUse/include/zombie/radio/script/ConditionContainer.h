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
#include "zombie/radio/script/ConditionContainer/Condition.h"

namespace zombie {
namespace radio {
namespace script {


class ConditionContainer {
public:
   private List<ConditionIter> conditions = std::make_unique<std::vector<>>();
    OperatorType operatorType = OperatorType.NONE;

    public ConditionContainer() {
      this(OperatorType.NONE);
   }

    public ConditionContainer(OperatorType var1) {
      this.operatorType = var1;
   }

    CompareResult Evaluate() {
    bool var2 = false;

      for (int var3 = 0; var3 < this.conditions.size(); var3++) {
    ConditionIter var4 = this.conditions.get(var3);
    CompareResult var1 = var4 != nullptr ? var4.Evaluate() : CompareResult.Invalid;
         if (var1 == CompareResult.Invalid)) {
    return var1;
         }

    OperatorType var5 = var4.getNextOperator();
         if (var3 == this.conditions.size() - 1) {
            return !var5 == OperatorType.NONE) ? CompareResult.Invalid : (!var2 ? var1 : CompareResult.False);
         }

         if (var5 == OperatorType.OR)) {
            if (!var2 && var1 == CompareResult.True)) {
    return var1;
            }

            var2 = false;
         } else if (var5 == OperatorType.AND)) {
            var2 = var2 || var1 == CompareResult.False);
         } else if (var5 == OperatorType.NONE)) {
            return CompareResult.Invalid;
         }
      }

      return CompareResult.Invalid;
   }

    OperatorType getNextOperator() {
      return this.operatorType;
   }

    void setNextOperator(OperatorType var1) {
      this.operatorType = var1;
   }

    void Add(ConditionContainer var1) {
      this.conditions.push_back(var1);
   }

    void Add(RadioGlobal var1, RadioGlobal var2, CompareMethod var3, OperatorType var4) {
    Condition var5 = std::make_shared<Condition>(var1, var2, var3, var4);
      this.conditions.push_back(var5);
   }
}
} // namespace script
} // namespace radio
} // namespace zombie
