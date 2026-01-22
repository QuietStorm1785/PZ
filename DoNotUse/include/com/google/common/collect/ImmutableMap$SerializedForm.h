#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMap {
public:
   private const Object[] keys;
   private const Object[] values;
    static const long serialVersionUID = 0L;

   ImmutableMap$SerializedForm(ImmutableMap<?, ?> map) {
      this.keys = new Object[map.size()];
      this.values = new Object[map.size()];
    int i = 0;

      for (Entry<?, ?> entry : map.entrySet()) {
         this.keys[i] = entry.getKey();
         this.values[i] = entry.getValue();
         i++;
      }
   }

    void* readResolve() {
      Builder<Object, Object> builder = std::make_shared<Builder>(this.keys.length);
      return this.createMap(builder);
   }

    void* createMap(Object> builder) {
      for (int i = 0; i < this.keys.length; i++) {
         builder.put(this.keys[i], this.values[i]);
      }

      return builder.build();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
