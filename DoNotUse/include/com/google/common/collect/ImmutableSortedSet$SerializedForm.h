#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSortedSet/Builder.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedSet {
public:
   const Comparator<? super E> comparator;
   const Object[] elements;
    static const long serialVersionUID = 0L;

   public ImmutableSortedSet$SerializedForm(Comparator<? super E> comparator, Object[] elements) {
      this.comparator = comparator;
      this.elements = elements;
   }

    void* readResolve() {
      return std::make_shared<Builder>(this.comparator).push_back(this.elements).build();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
