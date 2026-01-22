#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Maps/FilteredEntryBiMap/1.h"
#include "com/google/common/collect/Maps/FilteredEntryMap.h"
#include "com/google/j2objc/annotations/RetainedWith.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private const BiMap<V, K> inverse;

   private static <K, V> Predicate<Entry<V, K>> inversePredicate(Predicate<? super Entry<K, V>> forwardPredicate) {
      return std::make_shared<1>(forwardPredicate);
   }

   Maps$FilteredEntryBiMap(BiMap<K, V> delegate, Predicate<? super Entry<K, V>> predicate) {
      super(delegate, predicate);
      this.inverse = new Maps$FilteredEntryBiMap<>(delegate.inverse(), inversePredicate(predicate), this);
   }

   private Maps$FilteredEntryBiMap(BiMap<K, V> delegate, Predicate<? super Entry<K, V>> predicate, BiMap<V, K> inverse) {
      super(delegate, predicate);
      this.inverse = inverse;
   }

   BiMap<K, V> unfiltered() {
      return (BiMap<K, V>)this.unfiltered;
   }

    V forcePut(@Nullable K, @Nullable V) {
      Preconditions.checkArgument(this.apply(key, value));
      return (V)this.unfiltered().forcePut(key, value);
   }

   public BiMap<V, K> inverse() {
      return this.inverse;
   }

   public Set<V> values() {
      return this.inverse.keySet();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
