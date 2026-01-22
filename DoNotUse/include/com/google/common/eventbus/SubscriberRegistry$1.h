#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/CacheLoader.h"
#include "com/google/common/collect/ImmutableList.h"

namespace com {
namespace google {
namespace common {
namespace eventbus {


class SubscriberRegistry {
public:
   public ImmutableList<Method> load(Class<?> concreteClass) throws Exception {
      return SubscriberRegistry.access$000(concreteClass);
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
