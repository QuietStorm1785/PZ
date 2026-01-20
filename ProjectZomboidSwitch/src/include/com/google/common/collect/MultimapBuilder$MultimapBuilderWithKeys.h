#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/MultimapBuilder/ListMultimapBuilder.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys/1.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys/2.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys/3.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys/4.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys/5.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys/6.h"
#include "com/google/common/collect/MultimapBuilder/SetMultimapBuilder.h"
#include "com/google/common/collect/MultimapBuilder/SortedSetMultimapBuilder.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
    static const int DEFAULT_EXPECTED_VALUES_PER_KEY = 2;

   MultimapBuilder$MultimapBuilderWithKeys() {
   }

   abstract <K : public K0, V> Map<K, Collection<V>> createMap();

   public ListMultimapBuilder<K0, Object> arrayListValues() {
      return this.arrayListValues(2);
   }

   public ListMultimapBuilder<K0, Object> arrayListValues(int expectedValuesPerKey) {
      CollectPreconditions.checkNonnegative(expectedValuesPerKey, "expectedValuesPerKey");
      return std::make_shared<1>(this, expectedValuesPerKey);
   }

   public ListMultimapBuilder<K0, Object> linkedListValues() {
      return std::make_shared<2>(this);
   }

   public SetMultimapBuilder<K0, Object> hashSetValues() {
      return this.hashSetValues(2);
   }

   public SetMultimapBuilder<K0, Object> hashSetValues(int expectedValuesPerKey) {
      CollectPreconditions.checkNonnegative(expectedValuesPerKey, "expectedValuesPerKey");
      return std::make_shared<3>(this, expectedValuesPerKey);
   }

   public SetMultimapBuilder<K0, Object> linkedHashSetValues() {
      return this.linkedHashSetValues(2);
   }

   public SetMultimapBuilder<K0, Object> linkedHashSetValues(int expectedValuesPerKey) {
      CollectPreconditions.checkNonnegative(expectedValuesPerKey, "expectedValuesPerKey");
      return std::make_shared<4>(this, expectedValuesPerKey);
   }

   public SortedSetMultimapBuilder<K0, Comparable> treeSetValues() {
      return this.treeSetValues(Ordering.natural());
   }

   public <V0> SortedSetMultimapBuilder<K0, V0> treeSetValues(Comparator<V0> comparator) {
      Preconditions.checkNotNull(comparator, "comparator");
      return std::make_shared<5>(this, comparator);
   }

   public <V0 : public Enum<V0>> SetMultimapBuilder<K0, V0> enumSetValues(Class<V0> valueClass) {
      Preconditions.checkNotNull(valueClass, "valueClass");
      return std::make_shared<6>(this, valueClass);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
