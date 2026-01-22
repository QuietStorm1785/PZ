#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TLinkedHashSet {
public:
    bool changed;
   const Object[] set;
   const TObjectProcedure<? super E> procedure;

   public TLinkedHashSet$ForEachProcedure(Object[] var1, TObjectProcedure<? super E> set, TObjectProcedure procedure) {
      this.this$0 = var1;
      this.changed = false;
      this.set = set;
      this.procedure = procedure;
   }

    bool execute(int value) {
      return this.procedure.execute(this.set[value]);
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
