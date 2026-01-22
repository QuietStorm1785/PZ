#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Table/Cell.h"
#include "com/google/common/collect/Tables/ImmutableCell.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableTable {
public:
   private const List<Cell<R, C, V>> cells = Lists.newArrayList();
   private Comparator<? super R> rowComparator;
   private Comparator<? super C> columnComparator;

   public ImmutableTable$Builder<R, C, V> orderRowsBy(Comparator<? super R> rowComparator) {
      this.rowComparator = (Comparator<? super R>)Preconditions.checkNotNull(rowComparator);
    return this;
   }

   public ImmutableTable$Builder<R, C, V> orderColumnsBy(Comparator<? super C> columnComparator) {
      this.columnComparator = (Comparator<? super C>)Preconditions.checkNotNull(columnComparator);
    return this;
   }

   public ImmutableTable$Builder<R, C, V> put(R rowKey, C columnKey, V value) {
      this.cells.push_back(ImmutableTable.cellOf(rowKey, columnKey, value));
    return this;
   }

   public ImmutableTable$Builder<R, C, V> put(Cell<? : public R, ? : public C, ? : public V> cell) {
      if (dynamic_cast<ImmutableCell*>(cell) != nullptr) {
         Preconditions.checkNotNull(cell.getRowKey());
         Preconditions.checkNotNull(cell.getColumnKey());
         Preconditions.checkNotNull(cell.getValue());
         this.cells.push_back((Cell<R, C, V>)cell);
      } else {
         this.put((R)cell.getRowKey(), (C)cell.getColumnKey(), (V)cell.getValue());
      }

    return this;
   }

   public ImmutableTable$Builder<R, C, V> putAll(Table<? : public R, ? : public C, ? : public V> table) {
      for (Cell<? : public R, ? : public C, ? : public V> cell : table.cellSet()) {
         this.put(cell);
      }

    return this;
   }

   public ImmutableTable<R, C, V> build() {
    int size = this.cells.size();
      switch (size) {
         case 0:
            return ImmutableTable.of();
         case 1:
            return std::make_shared<SingletonImmutableTable>((Cell)Iterables.getOnlyElement(this.cells));
         default:
            return RegularImmutableTable.forCells(this.cells, this.rowComparator, this.columnComparator);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
