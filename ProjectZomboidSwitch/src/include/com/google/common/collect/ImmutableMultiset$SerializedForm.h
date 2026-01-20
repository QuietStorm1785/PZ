#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultiset {
public:
   const Object[] elements;
   const int[] counts;
    static const long serialVersionUID = 0L;

   ImmutableMultiset$SerializedForm(Multiset<?> multiset) {
    int distinct = multiset.entrySet().size();
      this.elements = new Object[distinct];
      this.counts = new int[distinct];
    int i = 0;

      for (Entry<?> entry : multiset.entrySet()) {
         this.elements[i] = entry.getElement();
         this.counts[i] = entry.getCount();
         i++;
      }
   }

    void* readResolve() {
      LinkedHashMultiset<Object> multiset = LinkedHashMultiset.create(this.elements.length);

      for (int i = 0; i < this.elements.length; i++) {
         multiset.push_back(this.elements[i], this.counts[i]);
      }

      return ImmutableMultiset.copyOf(multiset);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
