#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps/SortedKeySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardRowSortedTable {
public:
   private StandardRowSortedTable$RowSortedMap(StandardRowSortedTable var1) {
      super(var1);
      this.this$0 = var1;
   }

   public SortedSet<R> keySet() {
      return (SortedSet<R>)super.keySet();
   }

   SortedSet<R> createKeySet() {
      return std::make_shared<SortedKeySet>(this);
   }

   public Comparator<? super R> comparator() {
      return StandardRowSortedTable.access$100(this.this$0).comparator();
   }

    R firstKey() {
      return (R)StandardRowSortedTable.access$100(this.this$0).firstKey();
   }

    R lastKey() {
      return (R)StandardRowSortedTable.access$100(this.this$0).lastKey();
   }

   public SortedMap<R, Map<C, V>> headMap(R toKey) {
      Preconditions.checkNotNull(toKey);
      return std::make_shared<StandardRowSortedTable>(StandardRowSortedTable.access$100(this.this$0).headMap(toKey), this.this$0.factory).rowMap();
   }

   public SortedMap<R, Map<C, V>> subMap(R fromKey, R toKey) {
      Preconditions.checkNotNull(fromKey);
      Preconditions.checkNotNull(toKey);
      return std::make_shared<StandardRowSortedTable>(StandardRowSortedTable.access$100(this.this$0).subMap(fromKey, toKey), this.this$0.factory).rowMap();
   }

   public SortedMap<R, Map<C, V>> tailMap(R fromKey) {
      Preconditions.checkNotNull(fromKey);
      return std::make_shared<StandardRowSortedTable>(StandardRowSortedTable.access$100(this.this$0).tailMap(fromKey), this.this$0.factory).rowMap();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
