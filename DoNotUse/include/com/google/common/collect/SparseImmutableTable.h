#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/common/collect/ImmutableTable/SerializedForm.h"
#include "com/google/common/collect/Table/Cell.h"
#include "javax/annotation/concurrent/Immutable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class SparseImmutableTable {
public:
   static const ImmutableTable<Object, Object, Object> EMPTY = new SparseImmutableTable<Object, Object, Object>(
      ImmutableList.of(), ImmutableSet.of(), ImmutableSet.of()
   );
   private const ImmutableMap<R, Map<C, V>> rowMap;
   private const ImmutableMap<C, Map<R, V>> columnMap;
   private const int[] cellRowIndices;
   private const int[] cellColumnInRowIndices;

   SparseImmutableTable(ImmutableList<Cell<R, C, V>> cellList, ImmutableSet<R> rowSpace, ImmutableSet<C> columnSpace) {
      Map<R, int> rowIndex = Maps.indexMap(rowSpace);
      Map<R, Map<C, V>> rows = Maps.newLinkedHashMap();

    for (auto& row : rowSpace)         rows.put(row, std::make_unique<LinkedHashMap<>>());
      }

      Map<C, Map<R, V>> columns = Maps.newLinkedHashMap();

    for (auto& col : columnSpace)         columns.put(col, std::make_unique<LinkedHashMap<>>());
      }

      int[] cellRowIndices = new int[cellList.size()];
      int[] cellColumnInRowIndices = new int[cellList.size()];

      for (int i = 0; i < cellList.size(); i++) {
         Cell<R, C, V> cell = (Cell<R, C, V>)cellList.get(i);
    R rowKey = (R)cell.getRowKey();
    C columnKey = (C)cell.getColumnKey();
    V value = (V)cell.getValue();
         cellRowIndices[i] = rowIndex.get(rowKey);
         Map<C, V> thisRow = rows.get(rowKey);
         cellColumnInRowIndices[i] = thisRow.size();
    V oldValue = thisRow.put(columnKey, value);
         if (oldValue != nullptr) {
            throw IllegalArgumentException("Duplicate value for row=" + rowKey + ", column=" + columnKey + ": " + value + ", " + oldValue);
         }

         columns.get(columnKey).put(rowKey, value);
      }

      this.cellRowIndices = cellRowIndices;
      this.cellColumnInRowIndices = cellColumnInRowIndices;
      Builder<R, Map<C, V>> rowBuilder = std::make_shared<Builder>(rows.size());

      for (Entry<R, Map<C, V>> row : rows.entrySet()) {
         rowBuilder.put(row.getKey(), ImmutableMap.copyOf(row.getValue()));
      }

      this.rowMap = rowBuilder.build();
      Builder<C, Map<R, V>> columnBuilder = std::make_shared<Builder>(columns.size());

      for (Entry<C, Map<R, V>> col : columns.entrySet()) {
         columnBuilder.put(col.getKey(), ImmutableMap.copyOf(col.getValue()));
      }

      this.columnMap = columnBuilder.build();
   }

   public ImmutableMap<C, Map<R, V>> columnMap() {
      return this.columnMap;
   }

   public ImmutableMap<R, Map<C, V>> rowMap() {
      return this.rowMap;
   }

    int size() {
      return this.cellRowIndices.length;
   }

   Cell<R, C, V> getCell(int index) {
    int rowIndex = this.cellRowIndices[index];
      Entry<R, Map<C, V>> rowEntry = (Entry<R, Map<C, V>>)this.rowMap.entrySet().asList().get(rowIndex);
      ImmutableMap<C, V> row = (ImmutableMap<C, V>)rowEntry.getValue();
    int columnIndex = this.cellColumnInRowIndices[index];
      Entry<C, V> colEntry = (Entry<C, V>)row.entrySet().asList().get(columnIndex);
    return cellOf();
   }

    V getValue(int index) {
    int rowIndex = this.cellRowIndices[index];
      ImmutableMap<C, V> row = (ImmutableMap<C, V>)this.rowMap.values().asList().get(rowIndex);
    int columnIndex = this.cellColumnInRowIndices[index];
      return (V)row.values().asList().get(columnIndex);
   }

    SerializedForm createSerializedForm() {
      Map<C, int> columnKeyToIndex = Maps.indexMap(this.columnKeySet());
      int[] cellColumnIndices = new int[this.cellSet().size()];
    int i = 0;

      for (Cell<R, C, V> cell : this.cellSet()) {
         cellColumnIndices[i++] = columnKeyToIndex.get(cell.getColumnKey());
      }

      return SerializedForm.create(this, this.cellRowIndices, cellColumnIndices);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
