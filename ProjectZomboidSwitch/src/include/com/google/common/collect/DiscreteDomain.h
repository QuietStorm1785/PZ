#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/DiscreteDomain/BigIntegerDomain.h"
#include "com/google/common/collect/DiscreteDomain/IntegerDomain.h"
#include "com/google/common/collect/DiscreteDomain/LongDomain.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "java/math/BigInteger.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class DiscreteDomain {
public:
   public static DiscreteDomain<int> integers() {
      return IntegerDomain.access$000();
   }

   public static DiscreteDomain<int64_t> longs() {
      return LongDomain.access$100();
   }

   public static DiscreteDomain<BigInteger> bigIntegers() {
      return BigIntegerDomain.access$200();
   }

    protected DiscreteDomain() {
   }

   public abstract C next(C var1);

   public abstract C previous(C var1);

   public abstract long distance(C var1, C var2);

    C minValue() {
      throw std::make_unique<NoSuchElementException>();
   }

    C maxValue() {
      throw std::make_unique<NoSuchElementException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
