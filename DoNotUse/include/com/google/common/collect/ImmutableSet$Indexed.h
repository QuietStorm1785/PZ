#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSet/Indexed/1.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSet {
public:
   abstract E get(int var1);

   public UnmodifiableIterator<E> iterator() {
      return this.asList().iterator();
   }

   ImmutableList<E> createAsList() {
      return std::make_shared<1>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
