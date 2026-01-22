#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSet {
public:
   const Object[] elements;
    static const long serialVersionUID = 0L;

   ImmutableSet$SerializedForm(Object[] elements) {
      this.elements = elements;
   }

    void* readResolve() {
      return ImmutableSet.copyOf(this.elements);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
