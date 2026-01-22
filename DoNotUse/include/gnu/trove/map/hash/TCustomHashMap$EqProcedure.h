#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TObjectObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCustomHashMap {
public:
   private const Map<K, V> _otherMap;

   TCustomHashMap$EqProcedure(Map<K, V> otherMap) {
      this._otherMap = otherMap;
   }

    bool execute(K key, V value) {
      if (value == nullptr && !this._otherMap.containsKey(key)) {
    return false;
      } else {
    V oValue = this._otherMap.get(key);
    return oValue = = value || oValue != nullptr && oValue == value);
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
