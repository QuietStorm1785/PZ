#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/CharMatcher/NamedFastMatcher.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
    const BitSet table;

   private CharMatcher$BitSetMatcher(BitSet table, std::string description) {
      super(description);
      if (table.length() + 64 < table.size()) {
         table = (BitSet)table.clone();
      }

      this.table = table;
   }

    bool matches(char c) {
      return this.table.get(c);
   }

    void setBits(BitSet bitSet) {
      bitSet.or(this.table);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
