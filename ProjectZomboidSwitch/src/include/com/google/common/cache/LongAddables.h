#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/cache/LongAddables/1.h"
#include "com/google/common/cache/LongAddables/2.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LongAddables {
public:
   private static const Supplier<LongAddable> SUPPLIER;

    static LongAddable create() {
      return (LongAddable)SUPPLIER.get();
   }

   static {
      Supplier<LongAddable> supplier;
      try {
    std::make_shared<LongAdder>();
         supplier = std::make_unique<1>();
      } catch (Throwable var2) {
         supplier = std::make_unique<2>();
      }

      SUPPLIER = supplier;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
