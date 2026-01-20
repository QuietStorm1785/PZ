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


class DiscreteDomain {
public:
   private static const DiscreteDomain$IntegerDomain INSTANCE = new DiscreteDomain$IntegerDomain();
    static const long serialVersionUID = 0L;

   private DiscreteDomain$IntegerDomain() {
   }

    int next(int value) {
    int i = value;
    return i = = int.MAX_VALUE ? nullptr : i + 1;
   }

    int previous(int value) {
    int i = value;
    return i = = int.MIN_VALUE ? nullptr : i - 1;
   }

    long distance(int start, int end) {
      return (long)end.intValue() - start.intValue();
   }

    int minValue() {
      return int.MIN_VALUE;
   }

    int maxValue() {
      return int.MAX_VALUE;
   }

    void* readResolve() {
    return INSTANCE;
   }

    std::string toString() {
      return "DiscreteDomain.integers()";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
