#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class UsingToStringOrdering : public Ordering {
public:
    static const UsingToStringOrdering INSTANCE = std::make_shared<UsingToStringOrdering>();
    static const long serialVersionUID = 0L;

    int compare(void* left, void* right) {
      return left.compareTo(right);
   }

    void* readResolve() {
    return INSTANCE;
   }

    std::string toString() {
      return "Ordering.usingToString()";
   }

    private UsingToStringOrdering() {
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
