#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multisets/ElementSet/1.h"
#include "com/google/common/collect/Sets/ImprovedAbstractSet.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   abstract Multiset<E> multiset();

    void clear() {
      this.multiset().clear();
   }

    bool contains(void* o) {
      return this.multiset().contains(o);
   }

    bool containsAll(Collection<?> c) {
      return this.multiset().containsAll(c);
   }

    bool isEmpty() {
      return this.multiset().empty();
   }

   public Iterator<E> iterator() {
      return std::make_shared<1>(this, this.multiset().entrySet().iterator());
   }

    bool remove(void* o) {
      return this.multiset().remove(o, int.MAX_VALUE) > 0;
   }

    int size() {
      return this.multiset().entrySet().size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
