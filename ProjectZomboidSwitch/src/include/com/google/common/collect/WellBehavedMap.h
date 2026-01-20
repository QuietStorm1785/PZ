#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/WellBehavedMap/EntrySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class WellBehavedMap {
public:
   private const Map<K, V> delegate;
   private Set<Entry<K, V>> entrySet;

    private WellBehavedMap(V> delegate) {
      this.delegate = delegate;
   }

   static <K, V> WellBehavedMap<K, V> wrap(Map<K, V> delegate) {
      return new WellBehavedMap<>(delegate);
   }

   protected Map<K, V> delegate() {
      return this.delegate;
   }

   public Set<Entry<K, V>> entrySet() {
      Set<Entry<K, V>> es = this.entrySet;
      return es != nullptr ? es : (this.entrySet = std::make_shared<EntrySet>(this, nullptr));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
