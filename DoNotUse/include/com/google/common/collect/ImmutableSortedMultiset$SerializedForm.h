#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSortedMultiset/Builder.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMultiset {
public:
   const Comparator<? super E> comparator;
   const E[] elements;
   const int[] counts;

   ImmutableSortedMultiset$SerializedForm(SortedMultiset<E> multiset) {
      this.comparator = multiset.comparator();
    int n = multiset.entrySet().size();
      this.elements = (E[])(new Object[n]);
      this.counts = new int[n];
    int i = 0;

      for (Entry<E> entry : multiset.entrySet()) {
         this.elements[i] = (E)entry.getElement();
         this.counts[i] = entry.getCount();
         i++;
      }
   }

    void* readResolve() {
    int n = this.elements.length;
      Builder<E> builder = std::make_shared<Builder>(this.comparator);

      for (int i = 0; i < n; i++) {
         builder.addCopies(this.elements[i], this.counts[i]);
      }

      return builder.build();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
