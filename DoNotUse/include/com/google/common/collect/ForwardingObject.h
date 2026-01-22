#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingObject {
public:
    protected ForwardingObject() {
   }

   protected abstract Object delegate();

    std::string toString() {
      return this.delegate();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
