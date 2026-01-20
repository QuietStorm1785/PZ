#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Collections2/FilteredCollection.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   Sets$FilteredSet(Set<E> unfiltered, Predicate<? super E> predicate) {
      super(unfiltered, predicate);
   }

    bool equals(@Nullable Object) {
      return Sets.equalsImpl(this, object);
   }

    int hashCode() {
      return Sets.hashCodeImpl(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
