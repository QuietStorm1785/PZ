#pragma once
#include "zombie/util/AbstractIntCollection.h"
#include "zombie/util/IntIterator.h"
#include "zombie/util/hash/DefaultIntHashFunction.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace set {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AbstractIntSet : public AbstractIntCollection {
public:
protected
  AbstractIntSet() {}

  bool equals(void *object) {
    if (!(object instanceof IntSet intSet)) {
      return false;
    } else {
      return intSet.size() != this.size() ? false : this.containsAll(intSet);
    }
  }

  int hashCode() {
    int int0 = 0;
    IntIterator intIterator = this.iterator();

    while (intIterator.hasNext()) {
      int0 += DefaultIntHashFunction.INSTANCE.hash(intIterator.next());
    }

    return int0;
  }
}
} // namespace set
} // namespace util
} // namespace zombie
