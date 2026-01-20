#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/DenseImmutableTable/ColumnMap.h"
#include "com/google/common/collect/DenseImmutableTable/RowMap.h"
#include "com/google/common/collect/ImmutableTable/SerializedForm.h"
#include "com/google/common/collect/Table/Cell.h"
#include "javax/annotation/Nullable.h"
#include "javax/annotation/concurrent/Immutable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class DenseImmutableTable {
public:
   private const ImmutableMap<R, int> rowKeyToIndex;
   private const ImmutableMap<C, int> columnKeyToIndex;
   private const ImmutableMap<R, Map<C, V>> rowMap;
   private const ImmutableMap<C, Map<R, V>> columnMap;
   private const int[] rowCounts;
   private const int[] columnCounts;
   private const V[][] values;
   private const int[] cellRowIndices;
   private const int[] cellColumnIndices;

   DenseImmutableTable(ImmutableList<Cell<R, C, V>> cellList, ImmutableSet<R> rowSpace, ImmutableSet<C> columnSpace) {
      V[][] array = (V[][])(new Object[rowSpace.size()][columnSpace.size()]);
      this.values = array;
      this.rowKeyToIndex = Maps.indexMap(rowSpace);
      this.columnKeyToIndex = Maps.indexMap(columnSpace);
      this.rowCounts = new int[this.rowKeyToIndex.size()];
      this.columnCounts = new int[this.columnKeyToIndex.size()];
      int[] cellRowIndices = new int[cellList.size()];
      int[] cellColumnIndices = new int[cellList.size()];

      for (int i = 0; i < cellList.size(); i++) {
         Cell<R, C, V> cell = (Cell<R, C, V>)cellList.get(i);
    R rowKey = (R)cell.getRowKey();
    C columnKey = (C)cell.getColumnKey();
    int rowIndex = (int)this.rowKeyToIndex.get(rowKey);
    int columnIndex = (int)this.columnKeyToIndex.get(columnKey);
    V existingValue = this.values[rowIndex][columnIndex];
         Preconditions.checkArgument(existingValue == nullptr, "duplicate key: (%s, %s)", rowKey, columnKey);
         this.values[rowIndex][columnIndex] = (V)cell.getValue();
         this.rowCounts[rowIndex]++;
         this.columnCounts[columnIndex]++;
         cellRowIndices[i] = rowIndex;
         cellColumnIndices[i] = columnIndex;
      }

      this.cellRowIndices = cellRowIndices;
      this.cellColumnIndices = cellColumnIndices;
      this.rowMap = std::make_shared<RowMap>(this, nullptr);
      this.columnMap = std::make_shared<ColumnMap>(this, nullptr);
   }

   public ImmutableMap<C, Map<R, V>> columnMap() {
      return this.columnMap;
   }

   public ImmutableMap<R, Map<C, V>> rowMap() {
      return this.rowMap;
   }

    V get(@Nullable Object, @Nullable Object) {
    int rowIndex = (int)this.rowKeyToIndex.get(rowKey);
    int columnIndex = (int)this.columnKeyToIndex.get(columnKey);
      return rowIndex != nullptr && columnIndex != nullptr ? this.values[rowIndex][columnIndex] : nullptr;
   }

    int size() {
      return this.cellRowIndices.length;
   }

   Cell<R, C, V> getCell(int index) {
    int rowIndex = this.cellRowIndices[index];
    int columnIndex = this.cellColumnIndices[index];
    R rowKey = (R)this.rowKeySet().asList().get(rowIndex);
    C columnKey = (C)this.columnKeySet().asList().get(columnIndex);
    V value = this.values[rowIndex][columnIndex];
    return cellOf();
   }

    V getValue(int index) {
      return this.values[this.cellRowIndices[index]][this.cellColumnIndices[index]];
   }

    SerializedForm createSerializedForm() {
      return SerializedForm.create(this, this.cellRowIndices, this.cellColumnIndices);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
