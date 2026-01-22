#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace globals {

class EditGlobal {
public:
    RadioGlobal global;
    RadioGlobal value;
    EditGlobalOps operator;

    public EditGlobal(RadioGlobal var1, EditGlobalOps var2, RadioGlobal var3) {
      this.global = var1;
      this.operator = var2;
      this.value = var3;
   }

    RadioGlobal getGlobal() {
      return this.global;
   }

    EditGlobalOps getOperator() {
      return this.operator;
   }

    RadioGlobal getValue() {
      return this.value;
   }
}
} // namespace globals
} // namespace radio
} // namespace zombie
