#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MultimapBuilder/SetMultimapBuilder.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
   MultimapBuilder$SortedSetMultimapBuilder() {
   }

   public abstract <K : public K0, V : public V0> SortedSetMultimap<K, V> build();

   public <K : public K0, V : public V0> SortedSetMultimap<K, V> build(Multimap<? : public K, ? : public V> multimap) {
      return (SortedSetMultimap<K, V>)super.build(multimap);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
