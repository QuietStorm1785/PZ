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
   static const Equivalence$Identity INSTANCE = new Equivalence$Identity();
    static const long serialVersionUID = 1L;

    bool doEquivalent(void* a, void* b) {
    return false;
   }

    int doHash(void* o) {
      return System.identityHashCode(o);
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
