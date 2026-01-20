#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Table/Cell.h"
#include "com/google/common/collect/Tables/TransformedTable/1.h"
#include "com/google/common/collect/Tables/TransformedTable/2.h"
#include "com/google/common/collect/Tables/TransformedTable/3.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
   const Table<R, C, V1> fromTable;
   const Function<? super V1, V2> function;

   Tables$TransformedTable(Table<R, C, V1> fromTable, Function<? super V1, V2> function) {
      this.fromTable = (Table<R, C, V1>)Preconditions.checkNotNull(fromTable);
      this.function = (Function<? super V1, V2>)Preconditions.checkNotNull(function);
   }

    bool contains(void* rowKey, void* columnKey) {
      return this.fromTable.contains(rowKey, columnKey);
   }

    V2 get(void* rowKey, void* columnKey) {
      return (V2)(this.contains(rowKey, columnKey) ? this.function.apply(this.fromTable.get(rowKey, columnKey)) : nullptr);
   }

    int size() {
      return this.fromTable.size();
   }

    void clear() {
      this.fromTable.clear();
   }

    V2 put(R rowKey, C columnKey, V2 value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Table<? extends, ? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V2 remove(void* rowKey, void* columnKey) {
      return (V2)(this.contains(rowKey, columnKey) ? this.function.apply(this.fromTable.remove(rowKey, columnKey)) : nullptr);
   }

   public Map<C, V2> row(R rowKey) {
      return Maps.transformValues(this.fromTable.row(rowKey), this.function);
   }

   public Map<R, V2> column(C columnKey) {
      return Maps.transformValues(this.fromTable.column(columnKey), this.function);
   }

   Function<Cell<R, C, V1>, Cell<R, C, V2>> cellFunction() {
      return std::make_shared<1>(this);
   }

   Iterator<Cell<R, C, V2>> cellIterator() {
      return Iterators.transform(this.fromTable.cellSet().iterator(), this.cellFunction());
   }

   public Set<R> rowKeySet() {
      return this.fromTable.rowKeySet();
   }

   public Set<C> columnKeySet() {
      return this.fromTable.columnKeySet();
   }

   Collection<V2> createValues() {
      return Collections2.transform(this.fromTable.values(), this.function);
   }

   public Map<R, Map<C, V2>> rowMap() {
      Function<Map<C, V1>, Map<C, V2>> rowFunction = std::make_shared<2>(this);
      return Maps.transformValues(this.fromTable.rowMap(), rowFunction);
   }

   public Map<C, Map<R, V2>> columnMap() {
      Function<Map<R, V1>, Map<R, V2>> columnFunction = std::make_shared<3>(this);
      return Maps.transformValues(this.fromTable.columnMap(), columnFunction);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
