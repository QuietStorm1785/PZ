#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap/SerializedForm.h"
#include "com/google/common/collect/ImmutableSortedMap/Builder.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMap {
public:
   private const Comparator<Object> comparator;
    static const long serialVersionUID = 0L;

   ImmutableSortedMap$SerializedForm(ImmutableSortedMap<?, ?> sortedMap) {
      super(sortedMap);
      this.comparator = sortedMap.comparator();
   }

    void* readResolve() {
      Builder<Object, Object> builder = std::make_shared<Builder>(this.comparator);
      return this.createMap(builder);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
