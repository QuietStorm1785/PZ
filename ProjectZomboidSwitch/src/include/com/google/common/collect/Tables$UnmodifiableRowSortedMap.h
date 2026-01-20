#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Tables/UnmodifiableTable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
    static const long serialVersionUID = 0L;

   public Tables$UnmodifiableRowSortedMap(RowSortedTable<R, ? : public C, ? : public V> delegate) {
      super(delegate);
   }

   protected RowSortedTable<R, C, V> delegate() {
      return (RowSortedTable<R, C, V>)super.delegate();
   }

   public SortedMap<R, Map<C, V>> rowMap() {
      Function<Map<C, V>, Map<C, V>> wrapper = Tables.access$000();
      return Collections.unmodifiableSortedMap(Maps.transformValues(this.delegate().rowMap(), wrapper));
   }

   public SortedSet<R> rowKeySet() {
      return Collections.unmodifiableSortedSet(this.delegate().rowKeySet());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
