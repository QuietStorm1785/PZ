#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "com/google/j2objc/annotations/RetainedWith.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class SingletonImmutableBiMap {
public:
   const transient K singleKey;
   const transient V singleValue;
   transient ImmutableBiMap<V, K> inverse;

   SingletonImmutableBiMap(K singleKey, V singleValue) {
      CollectPreconditions.checkEntryNotNull(singleKey, singleValue);
      this.singleKey = singleKey;
      this.singleValue = singleValue;
   }

    private SingletonImmutableBiMap(K singleKey, V singleValue, K> inverse) {
      this.singleKey = singleKey;
      this.singleValue = singleValue;
      this.inverse = inverse;
   }

    V get(@Nullable Object) {
      return this.singleKey == key) ? this.singleValue : nullptr;
   }

    int size() {
    return 1;
   }

    bool containsKey(@Nullable Object) {
      return this.singleKey == key);
   }

    bool containsValue(@Nullable Object) {
      return this.singleValue == value);
   }

    bool isPartialView() {
    return false;
   }

   ImmutableSet<Entry<K, V>> createEntrySet() {
      return ImmutableSet.of(Maps.immutableEntry(this.singleKey, this.singleValue));
   }

   ImmutableSet<K> createKeySet() {
      return ImmutableSet.of(this.singleKey);
   }

   public ImmutableBiMap<V, K> inverse() {
      ImmutableBiMap<V, K> result = this.inverse;
    return result = = nullptr ? (this.inverse = new SingletonImmutableBiMap<>(this.singleValue, this.singleKey, this)) : result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
