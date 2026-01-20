#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableTable/SerializedForm.h"
#include "com/google/common/collect/Table/Cell.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class SingletonImmutableTable {
public:
    const R singleRowKey;
    const C singleColumnKey;
    const V singleValue;

   SingletonImmutableTable(R rowKey, C columnKey, V value) {
      this.singleRowKey = (R)Preconditions.checkNotNull(rowKey);
      this.singleColumnKey = (C)Preconditions.checkNotNull(columnKey);
      this.singleValue = (V)Preconditions.checkNotNull(value);
   }

   SingletonImmutableTable(Cell<R, C, V> cell) {
      this((R)cell.getRowKey(), (C)cell.getColumnKey(), (V)cell.getValue());
   }

   public ImmutableMap<R, V> column(C columnKey) {
      Preconditions.checkNotNull(columnKey);
      return this.containsColumn(columnKey) ? ImmutableMap.of(this.singleRowKey, this.singleValue) : ImmutableMap.of();
   }

   public ImmutableMap<C, Map<R, V>> columnMap() {
      return ImmutableMap.of(this.singleColumnKey, ImmutableMap.of(this.singleRowKey, this.singleValue));
   }

   public ImmutableMap<R, Map<C, V>> rowMap() {
      return ImmutableMap.of(this.singleRowKey, ImmutableMap.of(this.singleColumnKey, this.singleValue));
   }

    int size() {
    return 1;
   }

   ImmutableSet<Cell<R, C, V>> createCellSet() {
      return ImmutableSet.of(cellOf(this.singleRowKey, this.singleColumnKey, this.singleValue));
   }

   ImmutableCollection<V> createValues() {
      return ImmutableSet.of(this.singleValue);
   }

    SerializedForm createSerializedForm() {
      return SerializedForm.create(this, new int[]{0}, new int[]{0});
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
