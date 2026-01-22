#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheLoader {
public:
   private const Function<K, V> computingFunction;
    static const long serialVersionUID = 0L;

   public CacheLoader$FunctionToCacheLoader(Function<K, V> computingFunction) {
      this.computingFunction = (Function<K, V>)Preconditions.checkNotNull(computingFunction);
   }

    V load(K key) {
      return (V)this.computingFunction.apply(Preconditions.checkNotNull(key));
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
