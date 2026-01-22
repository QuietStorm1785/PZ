#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashIterator.h"
#include "gnu/trove/impl/hash/TObjectHash.h"

namespace gnu {
namespace trove {
namespace iterator {
namespace hash {


class TObjectHashIterator {
public:
    const TObjectHash _objectHash;

    public TObjectHashIterator(TObjectHash<E> hash) {
      super(hash);
      this._objectHash = hash;
   }

    E objectAtIndex(int index) {
    void* obj = this._objectHash._set[index];
      return (E)(obj != TObjectHash.FREE && obj != TObjectHash.REMOVED ? obj : nullptr);
   }
}
} // namespace hash
} // namespace iterator
} // namespace trove
} // namespace gnu
