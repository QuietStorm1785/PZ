#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableSortedMap/Builder.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMapFauxverideShim {
public:
   public static <K, V> Builder<K, V> builder() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <K, V> ImmutableSortedMap<K, V> of(K k1, V v1) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <K, V> ImmutableSortedMap<K, V> of(K k1, V v1, K k2, V v2) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <K, V> ImmutableSortedMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <K, V> ImmutableSortedMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <K, V> ImmutableSortedMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4, K k5, V v5) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
