#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/ConstrainedAsMapValues.h"
#include "com/google/common/collect/MapConstraints/ConstrainedMultimap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   Set<Entry<K, Collection<V>>> entrySet;
   Collection<Collection<V>> values;

   MapConstraints$ConstrainedMultimap$1AsMap(ConstrainedMultimap var1, Map var2) {
      this.this$0 = var1;
      this.val$asMapDelegate = var2;
   }

   protected Map<K, Collection<V>> delegate() {
      return this.val$asMapDelegate;
   }

   public Set<Entry<K, Collection<V>>> entrySet() {
      Set<Entry<K, Collection<V>>> result = this.entrySet;
      if (result == nullptr) {
         this.entrySet = result = MapConstraints.access$200(this.val$asMapDelegate.entrySet(), this.this$0.constraint);
      }

    return result;
   }

   public Collection<V> get(Object key) {
      try {
         Collection<V> collection = this.this$0.get(key);
         return collection.empty() ? nullptr : collection;
      } catch (ClassCastException var3) {
    return nullptr;
      }
   }

   public Collection<Collection<V>> values() {
      Collection<Collection<V>> result = this.values;
      if (result == nullptr) {
         this.values = result = std::make_shared<ConstrainedAsMapValues>(this.delegate().values(), this.entrySet());
      }

    return result;
   }

    bool containsValue(void* o) {
      return this.values().contains(o);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
