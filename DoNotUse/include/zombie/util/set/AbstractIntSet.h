#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/AbstractIntCollection.h"
#include "zombie/util/IntIterator.h"
#include "zombie/util/hash/DefaultIntHashFunction.h"

namespace zombie {
namespace util {
namespace set {


class AbstractIntSet : public AbstractIntCollection {
public:
    protected AbstractIntSet() {
   }

    bool equals(void* var1) {
      if (!(dynamic_cast<IntSet*>(var1) != nullptr var2)) {
    return false;
      } else {
         return var2.size() != this.size() ? false : this.containsAll(var2);
      }
   }

    int hashCode() {
    int var1 = 0;
    IntIterator var2 = this.iterator();

      while (var2.hasNext()) {
         var1 += DefaultIntHashFunction.INSTANCE.hash(var2.next());
      }

    return var1;
   }
}
} // namespace set
} // namespace util
} // namespace zombie
