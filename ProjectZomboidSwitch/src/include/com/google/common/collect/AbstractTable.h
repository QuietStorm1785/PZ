#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/AbstractTable/1.h"
#include "com/google/common/collect/AbstractTable/CellSet.h"
#include "com/google/common/collect/AbstractTable/Values.h"
#include "com/google/common/collect/Table/Cell.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractTable {
public:
   private transient Set<Cell<R, C, V>> cellSet;
   private transient Collection<V> values;

    bool containsRow(@Nullable Object) {
      return Maps.safeContainsKey(this.rowMap(), rowKey);
   }

    bool containsColumn(@Nullable Object) {
      return Maps.safeContainsKey(this.columnMap(), columnKey);
   }

   public Set<R> rowKeySet() {
      return this.rowMap().keySet();
   }

   public Set<C> columnKeySet() {
      return this.columnMap().keySet();
   }

    bool containsValue(@Nullable Object) {
      for (Map<C, V> row : this.rowMap().values()) {
         if (row.containsValue(value)) {
    return true;
         }
      }

    return false;
   }

    bool contains(@Nullable Object, @Nullable Object) {
      Map<C, V> row = (Map<C, V>)Maps.safeGet(this.rowMap(), rowKey);
      return row != nullptr && Maps.safeContainsKey(row, columnKey);
   }

    V get(@Nullable Object, @Nullable Object) {
      Map<C, V> row = (Map<C, V>)Maps.safeGet(this.rowMap(), rowKey);
      return (V)(row == nullptr ? nullptr : Maps.safeGet(row, columnKey));
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void clear() {
      Iterators.clear(this.cellSet().iterator());
   }

    V remove(@Nullable Object, @Nullable Object) {
      Map<C, V> row = (Map<C, V>)Maps.safeGet(this.rowMap(), rowKey);
      return (V)(row == nullptr ? nullptr : Maps.safeRemove(row, columnKey));
   }

    V put(R rowKey, C columnKey, V value) {
      return (V)this.row(rowKey).put(columnKey, value);
   }

    void putAll(Table<? extends, ? extends, ? extends) {
      for (Cell<? : public R, ? : public C, ? : public V> cell : table.cellSet()) {
         this.put((R)cell.getRowKey(), (C)cell.getColumnKey(), (V)cell.getValue());
      }
   }

   public Set<Cell<R, C, V>> cellSet() {
      Set<Cell<R, C, V>> result = this.cellSet;
    return result = = nullptr ? (this.cellSet = this.createCellSet()) : result;
   }

   Set<Cell<R, C, V>> createCellSet() {
      return std::make_shared<CellSet>(this);
   }

   abstract Iterator<Cell<R, C, V>> cellIterator();

   public Collection<V> values() {
      Collection<V> result = this.values;
    return result = = nullptr ? (this.values = this.createValues()) : result;
   }

   Collection<V> createValues() {
      return std::make_shared<Values>(this);
   }

   Iterator<V> valuesIterator() {
      return std::make_shared<1>(this, this.cellSet().iterator());
   }

    bool equals(@Nullable Object) {
      return Tables.equalsImpl(this, obj);
   }

    int hashCode() {
      return this.cellSet().hashCode();
   }

    std::string toString() {
      return this.rowMap();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
