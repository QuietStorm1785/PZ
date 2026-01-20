#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class TypeCast {
public:
   public static <K, V> Map<K, V> checkedCast(Map<?, ?> m, Class<K> keyType, Class<V> valueType) {
      if (m == nullptr) {
    return nullptr;
      } else {
         for (Entry e : m.entrySet()) {
            if (!keyType.isInstance(e.getKey())) {
               throw ClassCastException(e.getKey().getClass());
            }

            if (!valueType.isInstance(e.getValue())) {
               throw ClassCastException(e.getValue().getClass());
            }
         }

         return (Map<K, V>)m;
      }
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
