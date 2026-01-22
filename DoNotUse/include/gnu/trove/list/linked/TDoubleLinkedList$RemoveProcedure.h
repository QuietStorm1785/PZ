#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TDoubleProcedure.h"

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TDoubleLinkedList {
public:
    bool changed;

   TDoubleLinkedList$RemoveProcedure(TDoubleLinkedList var1) {
      this.this$0 = var1;
      this.changed = false;
   }

    bool execute(double value) {
      if (this.this$0.remove(value)) {
         this.changed = true;
      }

    return true;
   }

    bool isChanged() {
      return this.changed;
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
