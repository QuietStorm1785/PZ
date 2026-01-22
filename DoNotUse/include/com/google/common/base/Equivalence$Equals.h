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
namespace base {


class Equivalence {
public:
   static const Equivalence$Equals INSTANCE = new Equivalence$Equals();
    static const long serialVersionUID = 1L;

    bool doEquivalent(void* a, void* b) {
      return a == b);
   }

    int doHash(void* o) {
      return o.hashCode();
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
