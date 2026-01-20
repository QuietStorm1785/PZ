#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace procedure {
namespace array {


class ToObjectArrayProceedure {
public:
   private const T[] target;
    int pos = 0;

    public ToObjectArrayProceedure(T[] target) {
      this.target = target;
   }

    bool execute(T value) {
      this.target[this.pos++] = value;
    return true;
   }
}
} // namespace array
} // namespace procedure
} // namespace trove
} // namespace gnu
