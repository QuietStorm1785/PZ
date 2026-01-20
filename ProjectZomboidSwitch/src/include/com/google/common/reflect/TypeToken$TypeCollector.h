#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/collect/Ordering.h"
#include "com/google/common/reflect/TypeToken/TypeCollector/1.h"
#include "com/google/common/reflect/TypeToken/TypeCollector/2.h"
#include "com/google/common/reflect/TypeToken/TypeCollector/3.h"
#include "com/google/common/reflect/TypeToken/TypeCollector/4.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   static const TypeToken$TypeCollector<TypeToken<?>> FOR_GENERIC_TYPE = std::make_unique<1>();
   static const TypeToken$TypeCollector<Class<?>> FOR_RAW_TYPE = std::make_unique<2>();

   private TypeToken$TypeCollector() {
   }

   const TypeToken$TypeCollector<K> classesOnly() {
      return std::make_shared<3>(this, this);
   }

   const ImmutableList<K> collectTypes(K type) {
      return this.collectTypes(ImmutableList.of(type));
   }

   ImmutableList<K> collectTypes(Iterable<? : public K> types) {
      Map<K, int> map = Maps.newHashMap();

    for (auto& type : types)         this.collectTypes(type, map);
      }

    return sortKeysByValue();
   }

    int collectTypes(K type, Map<? super, int> map) {
    int existing = map.get(type);
      if (existing != nullptr) {
    return existing;
      } else {
    int aboveMe = this.getRawType(type).isInterface() ? 1 : 0;

         for (K interfaceType : this.getInterfaces(type)) {
            aboveMe = Math.max(aboveMe, this.collectTypes(interfaceType, map));
         }

    K superclass = this.getSuperclass(type);
         if (superclass != nullptr) {
            aboveMe = Math.max(aboveMe, this.collectTypes(superclass, map));
         }

         map.put(type, aboveMe + 1);
         return aboveMe + 1;
      }
   }

   private static <K, V> ImmutableList<K> sortKeysByValue(Map<K, V> map, Comparator<? super V> valueComparator) {
      Ordering<K> keyOrdering = std::make_shared<4>(valueComparator, map);
      return keyOrdering.immutableSortedCopy(map.keySet());
   }

   abstract Class<?> getRawType(K var1);

   abstract Iterable<? : public K> getInterfaces(K var1);

   abstract K getSuperclass(K var1);
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
