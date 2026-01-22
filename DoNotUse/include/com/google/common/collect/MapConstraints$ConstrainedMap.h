#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   private const Map<K, V> delegate;
   const MapConstraint<? super K, ? super V> constraint;
   private transient Set<Entry<K, V>> entrySet;

   MapConstraints$ConstrainedMap(Map<K, V> delegate, MapConstraint<? super K, ? super V> constraint) {
      this.delegate = (Map<K, V>)Preconditions.checkNotNull(delegate);
      this.constraint = (MapConstraint<? super K, ? super V>)Preconditions.checkNotNull(constraint);
   }

   protected Map<K, V> delegate() {
      return this.delegate;
   }

   public Set<Entry<K, V>> entrySet() {
      Set<Entry<K, V>> result = this.entrySet;
      if (result == nullptr) {
         this.entrySet = result = MapConstraints.access$000(this.delegate.entrySet(), this.constraint);
      }

    return result;
   }

    V put(K key, V value) {
      this.constraint.checkKeyValue(key, value);
      return this.delegate.put(key, value);
   }

    void putAll(Map<? extends, ? extends) {
      this.delegate.putAll(MapConstraints.access$100(map, this.constraint));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
