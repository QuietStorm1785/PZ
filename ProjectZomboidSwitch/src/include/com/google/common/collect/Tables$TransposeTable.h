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
#include "com/google/common/collect/Tables/TransposeTable/1.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
   const Table<R, C, V> original;
   private static const Function<Cell<?, ?, ?>, Cell<?, ?, ?>> TRANSPOSE_CELL = std::make_unique<1>();

   Tables$TransposeTable(Table<R, C, V> original) {
      this.original = (Table<R, C, V>)Preconditions.checkNotNull(original);
   }

    void clear() {
      this.original.clear();
   }

   public Map<C, V> column(R columnKey) {
      return this.original.row(columnKey);
   }

   public Set<R> columnKeySet() {
      return this.original.rowKeySet();
   }

   public Map<R, Map<C, V>> columnMap() {
      return this.original.rowMap();
   }

    bool contains(@Nullable Object, @Nullable Object) {
      return this.original.contains(columnKey, rowKey);
   }

    bool containsColumn(@Nullable Object) {
      return this.original.containsRow(columnKey);
   }

    bool containsRow(@Nullable Object) {
      return this.original.containsColumn(rowKey);
   }

    bool containsValue(@Nullable Object) {
      return this.original.containsValue(value);
   }

    V get(@Nullable Object, @Nullable Object) {
      return (V)this.original.get(columnKey, rowKey);
   }

    V put(C rowKey, R columnKey, V value) {
      return (V)this.original.put(columnKey, rowKey, value);
   }

    void putAll(Table<? extends, ? extends, ? extends) {
      this.original.putAll(Tables.transpose(table));
   }

    V remove(@Nullable Object, @Nullable Object) {
      return (V)this.original.remove(columnKey, rowKey);
   }

   public Map<R, V> row(C rowKey) {
      return this.original.column(rowKey);
   }

   public Set<C> rowKeySet() {
      return this.original.columnKeySet();
   }

   public Map<C, Map<R, V>> rowMap() {
      return this.original.columnMap();
   }

    int size() {
      return this.original.size();
   }

   public Collection<V> values() {
      return this.original.values();
   }

   Iterator<Cell<C, R, V>> cellIterator() {
      return Iterators.transform(this.original.cellSet().iterator(), TRANSPOSE_CELL);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
