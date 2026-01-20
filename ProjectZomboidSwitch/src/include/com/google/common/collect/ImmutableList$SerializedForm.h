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


class ImmutableList {
public:
   const Object[] elements;
    static const long serialVersionUID = 0L;

   ImmutableList$SerializedForm(Object[] elements) {
      this.elements = elements;
   }

    void* readResolve() {
      return ImmutableList.copyOf(this.elements);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
