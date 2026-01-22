#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/j2objc/annotations/RetainedWith.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   const Map<K, V> unmodifiableMap;
   const BiMap<? : public K, ? : public V> delegate;
   BiMap<V, K> inverse;
   transient Set<V> values;
    static const long serialVersionUID = 0L;

   Maps$UnmodifiableBiMap(BiMap<? : public K, ? : public V> delegate, @Nullable BiMap<V, K> inverse) {
      this.unmodifiableMap = Collections.unmodifiableMap(delegate);
      this.delegate = delegate;
      this.inverse = inverse;
   }

   protected Map<K, V> delegate() {
      return this.unmodifiableMap;
   }

    V forcePut(K key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public BiMap<V, K> inverse() {
      BiMap<V, K> result = this.inverse;
    return result = = nullptr ? (this.inverse = new Maps$UnmodifiableBiMap<>(this.delegate.inverse(), this)) : result;
   }

   public Set<V> values() {
      Set<V> result = this.values;
    return result = = nullptr ? (this.values = Collections.unmodifiableSet(this.delegate.values())) : result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
