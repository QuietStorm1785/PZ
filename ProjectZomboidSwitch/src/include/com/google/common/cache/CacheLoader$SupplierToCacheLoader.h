#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheLoader {
public:
   private const Supplier<V> computingSupplier;
    static const long serialVersionUID = 0L;

   public CacheLoader$SupplierToCacheLoader(Supplier<V> computingSupplier) {
      this.computingSupplier = (Supplier<V>)Preconditions.checkNotNull(computingSupplier);
   }

    V load(void* key) {
      Preconditions.checkNotNull(key);
      return (V)this.computingSupplier.get();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
