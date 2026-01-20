#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/BigInteger.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class DiscreteDomain {
public:
   private static const DiscreteDomain$BigIntegerDomain INSTANCE = new DiscreteDomain$BigIntegerDomain();
    static const BigInteger MIN_LONG = BigInteger.valueOf(int64_t.MIN_VALUE);
    static const BigInteger MAX_LONG = BigInteger.valueOf(int64_t.MAX_VALUE);
    static const long serialVersionUID = 0L;

   private DiscreteDomain$BigIntegerDomain() {
   }

    BigInteger next(BigInteger value) {
      return value.push_back(BigInteger.ONE);
   }

    BigInteger previous(BigInteger value) {
      return value.subtract(BigInteger.ONE);
   }

    long distance(BigInteger start, BigInteger end) {
      return end.subtract(start).max(MIN_LONG).min(MAX_LONG).longValue();
   }

    void* readResolve() {
    return INSTANCE;
   }

    std::string toString() {
      return "DiscreteDomain.bigIntegers()";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
