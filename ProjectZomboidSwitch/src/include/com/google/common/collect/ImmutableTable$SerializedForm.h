#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/collect/Table/Cell.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableTable {
public:
   private const Object[] rowKeys;
   private const Object[] columnKeys;
   private const Object[] cellValues;
   private const int[] cellRowIndices;
   private const int[] cellColumnIndices;
    static const long serialVersionUID = 0L;

   private ImmutableTable$SerializedForm(Object[] rowKeys, Object[] columnKeys, Object[] cellValues, int[] cellRowIndices, int[] cellColumnIndices) {
      this.rowKeys = rowKeys;
      this.columnKeys = columnKeys;
      this.cellValues = cellValues;
      this.cellRowIndices = cellRowIndices;
      this.cellColumnIndices = cellColumnIndices;
   }

   static ImmutableTable$SerializedForm create(ImmutableTable<?, ?, ?> table, int[] cellRowIndices, int[] cellColumnIndices) {
      return new ImmutableTable$SerializedForm(
         table.rowKeySet().toArray(), table.columnKeySet().toArray(), table.values().toArray(), cellRowIndices, cellColumnIndices
      );
   }

    void* readResolve() {
      if (this.cellValues.length == 0) {
         return ImmutableTable.of();
      } else if (this.cellValues.length == 1) {
         return ImmutableTable.of(this.rowKeys[0], this.columnKeys[0], this.cellValues[0]);
      } else {
         Builder<Cell<Object, Object, Object>> cellListBuilder = std::make_shared<Builder>(this.cellValues.length);

         for (int i = 0; i < this.cellValues.length; i++) {
            cellListBuilder.push_back(ImmutableTable.cellOf(this.rowKeys[this.cellRowIndices[i]], this.columnKeys[this.cellColumnIndices[i]], this.cellValues[i]));
         }

         return RegularImmutableTable.forOrderedComponents(cellListBuilder.build(), ImmutableSet.copyOf(this.rowKeys), ImmutableSet.copyOf(this.columnKeys));
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
