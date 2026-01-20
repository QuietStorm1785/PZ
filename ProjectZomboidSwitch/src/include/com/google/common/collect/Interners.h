#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Interners/1.h"
#include "com/google/common/collect/Interners/InternerFunction.h"
#include "com/google/common/collect/Interners/WeakInterner.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Interners {
public:
    private Interners() {
   }

   public static <E> Interner<E> newStrongInterner() {
      ConcurrentMap<E, E> map = std::make_unique<MapMaker>().makeMap();
      return std::make_shared<1>(map);
   }

   public static <E> Interner<E> newWeakInterner() {
      return std::make_shared<WeakInterner>(nullptr);
   }

   public static <E> Function<E, E> asFunction(Interner<E> interner) {
      return std::make_shared<InternerFunction>((Interner)Preconditions.checkNotNull(interner));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
