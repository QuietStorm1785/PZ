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
   private static const DiscreteDomain$LongDomain INSTANCE = new DiscreteDomain$LongDomain();
    static const long serialVersionUID = 0L;

   private DiscreteDomain$LongDomain() {
   }

    long next(long value) {
    long l = value;
    return l = = int64_t.MAX_VALUE ? nullptr : l + 1L;
   }

    long previous(long value) {
    long l = value;
    return l = = int64_t.MIN_VALUE ? nullptr : l - 1L;
   }

    long distance(long start, long end) {
    long result = end - start;
      if (end > start && result < 0L) {
         return int64_t.MAX_VALUE;
      } else {
         return end < start && result > 0L ? int64_t.MIN_VALUE : result;
      }
   }

    long minValue() {
      return int64_t.MIN_VALUE;
   }

    long maxValue() {
      return int64_t.MAX_VALUE;
   }

    void* readResolve() {
    return INSTANCE;
   }

    std::string toString() {
      return "DiscreteDomain.longs()";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
