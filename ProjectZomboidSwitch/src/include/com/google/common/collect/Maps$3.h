#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$3(SortedSet var1) {
      this.val$set = var1;
   }

   protected SortedSet<E> delegate() {
      return this.val$set;
   }

    bool add(E element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public SortedSet<E> headSet(E toElement) {
      return Maps.access$300(super.headSet(toElement));
   }

   public SortedSet<E> subSet(E fromElement, E toElement) {
      return Maps.access$300(super.subSet(fromElement, toElement));
   }

   public SortedSet<E> tailSet(E fromElement) {
      return Maps.access$300(super.tailSet(fromElement));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
