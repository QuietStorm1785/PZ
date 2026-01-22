#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/MultimapBuilder/1.h"
#include "com/google/common/collect/MultimapBuilder/2.h"
#include "com/google/common/collect/MultimapBuilder/3.h"
#include "com/google/common/collect/MultimapBuilder/4.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
    static const int DEFAULT_EXPECTED_KEYS = 8;

    private MultimapBuilder() {
   }

   public static MultimapBuilderWithKeys<Object> hashKeys() {
    return hashKeys();
   }

   public static MultimapBuilderWithKeys<Object> hashKeys(int expectedKeys) {
      CollectPreconditions.checkNonnegative(expectedKeys, "expectedKeys");
      return std::make_shared<1>(expectedKeys);
   }

   public static MultimapBuilderWithKeys<Object> linkedHashKeys() {
    return linkedHashKeys();
   }

   public static MultimapBuilderWithKeys<Object> linkedHashKeys(int expectedKeys) {
      CollectPreconditions.checkNonnegative(expectedKeys, "expectedKeys");
      return std::make_shared<2>(expectedKeys);
   }

   public static MultimapBuilderWithKeys<Comparable> treeKeys() {
    return treeKeys();
   }

   public static <K0> MultimapBuilderWithKeys<K0> treeKeys(Comparator<K0> comparator) {
      Preconditions.checkNotNull(comparator);
      return std::make_shared<3>(comparator);
   }

   public static <K0 : public Enum<K0>> MultimapBuilderWithKeys<K0> enumKeys(Class<K0> keyClass) {
      Preconditions.checkNotNull(keyClass);
      return std::make_shared<4>(keyClass);
   }

   public abstract <K : public K0, V : public V0> Multimap<K, V> build();

   public <K : public K0, V : public V0> Multimap<K, V> build(Multimap<? : public K, ? : public V> multimap) {
      Multimap<K, V> result = this.build();
      result.putAll(multimap);
    return result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
