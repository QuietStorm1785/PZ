#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableBiMap/Builder.h"
#include "com/google/common/collect/ImmutableMap/SerializedForm.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableBiMap {
public:
    static const long serialVersionUID = 0L;

   ImmutableBiMap$SerializedForm(ImmutableBiMap<?, ?> bimap) {
      super(bimap);
   }

    void* readResolve() {
      Builder<Object, Object> builder = std::make_unique<Builder>();
      return this.createMap(builder);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
