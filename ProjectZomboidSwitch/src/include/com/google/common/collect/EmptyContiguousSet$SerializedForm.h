#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class EmptyContiguousSet {
public:
   private const DiscreteDomain<C> domain;
    static const long serialVersionUID = 0L;

   private EmptyContiguousSet$SerializedForm(DiscreteDomain<C> domain) {
      this.domain = domain;
   }

    void* readResolve() {
      return std::make_shared<EmptyContiguousSet>(this.domain);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
