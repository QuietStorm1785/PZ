#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/CacheLoader.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/reflect/TypeToken.h"

namespace com {
namespace google {
namespace common {
namespace eventbus {


class SubscriberRegistry {
public:
   public ImmutableSet<Class<?>> load(Class<?> concreteClass) {
      return ImmutableSet.copyOf(TypeToken.of(concreteClass).getTypes().rawTypes());
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
