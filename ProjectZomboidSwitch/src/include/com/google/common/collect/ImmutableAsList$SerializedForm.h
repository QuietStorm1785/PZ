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


class ImmutableAsList {
public:
   const ImmutableCollection<?> collection;
    static const long serialVersionUID = 0L;

   ImmutableAsList$SerializedForm(ImmutableCollection<?> collection) {
      this.collection = collection;
   }

    void* readResolve() {
      return this.collection.asList();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
