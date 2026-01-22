#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractBiMap {
public:
   private const Entry<K, V> delegate;

   AbstractBiMap$BiMapEntry(Entry<K, V> var1, Entry delegate) {
      this.this$0 = var1;
      this.delegate = delegate;
   }

   protected Entry<K, V> delegate() {
      return this.delegate;
   }

    V setValue(V value) {
      Preconditions.checkState(this.this$0.entrySet().contains(this), "entry no longer in map");
      if (Objects.equal(value, this.getValue())) {
    return value;
      } else {
         Preconditions.checkArgument(!this.this$0.containsValue(value), "value already present: %s", value);
    V oldValue = (V)this.delegate.setValue(value);
         Preconditions.checkState(Objects.equal(value, this.this$0.get(this.getKey())), "entry no longer in map");
         AbstractBiMap.access$500(this.this$0, this.getKey(), true, oldValue, value);
    return oldValue;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
