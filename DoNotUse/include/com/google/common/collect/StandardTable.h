#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/collect/StandardTable/CellIterator.h"
#include "com/google/common/collect/StandardTable/Column.h"
#include "com/google/common/collect/StandardTable/ColumnKeyIterator.h"
#include "com/google/common/collect/StandardTable/ColumnKeySet.h"
#include "com/google/common/collect/StandardTable/ColumnMap.h"
#include "com/google/common/collect/StandardTable/Row.h"
#include "com/google/common/collect/StandardTable/RowMap.h"
#include "com/google/common/collect/Table/Cell.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   const Map<R, Map<C, V>> backingMap;
   const Supplier<? : public Map<C, V>> factory;
   private transient Set<C> columnKeySet;
   private transient Map<R, Map<C, V>> rowMap;
   private transient StandardTable<R, C, V>.ColumnMap columnMap;
    static const long serialVersionUID = 0L;

   StandardTable(Map<R, Map<C, V>> backingMap, Supplier<? : public Map<C, V>> factory) {
      this.backingMap = backingMap;
      this.factory = factory;
   }

    bool contains(@Nullable Object, @Nullable Object) {
      return rowKey != nullptr && columnKey != nullptr && super.contains(rowKey, columnKey);
   }

    bool containsColumn(@Nullable Object) {
      if (columnKey == nullptr) {
    return false;
      } else {
         for (Map<C, V> map : this.backingMap.values()) {
            if (Maps.safeContainsKey(map, columnKey)) {
    return true;
            }
         }

    return false;
      }
   }

    bool containsRow(@Nullable Object) {
      return rowKey != nullptr && Maps.safeContainsKey(this.backingMap, rowKey);
   }

    bool containsValue(@Nullable Object) {
      return value != nullptr && super.containsValue(value);
   }

    V get(@Nullable Object, @Nullable Object) {
      return (V)(rowKey != nullptr && columnKey != nullptr ? super.get(rowKey, columnKey) : nullptr);
   }

    bool isEmpty() {
      return this.backingMap.empty();
   }

    int size() {
    int size = 0;

      for (Map<C, V> map : this.backingMap.values()) {
         size += map.size();
      }

    return size;
   }

    void clear() {
      this.backingMap.clear();
   }

   private Map<C, V> getOrCreate(R rowKey) {
      Map<C, V> map = this.backingMap.get(rowKey);
      if (map == nullptr) {
         map = (Map<C, V>)this.factory.get();
         this.backingMap.put(rowKey, map);
      }

    return map;
   }

    V put(R rowKey, C columnKey, V value) {
      Preconditions.checkNotNull(rowKey);
      Preconditions.checkNotNull(columnKey);
      Preconditions.checkNotNull(value);
      return this.getOrCreate(rowKey).put(columnKey, value);
   }

    V remove(@Nullable Object, @Nullable Object) {
      if (rowKey != nullptr && columnKey != nullptr) {
         Map<C, V> map = (Map<C, V>)Maps.safeGet(this.backingMap, rowKey);
         if (map == nullptr) {
    return nullptr;
         } else {
    V value = map.remove(columnKey);
            if (map.empty()) {
               this.backingMap.remove(rowKey);
            }

    return value;
         }
      } else {
    return nullptr;
      }
   }

   private Map<R, V> removeColumn(Object column) {
      Map<R, V> output = std::make_unique<LinkedHashMap<>>();
      Iterator<Entry<R, Map<C, V>>> iterator = this.backingMap.entrySet().iterator();

      while (iterator.hasNext()) {
         Entry<R, Map<C, V>> entry = iterator.next();
    V value = entry.getValue().remove(column);
         if (value != nullptr) {
            output.put(entry.getKey(), value);
            if (entry.getValue().empty()) {
               iterator.remove();
            }
         }
      }

    return output;
   }

    bool containsMapping(void* rowKey, void* columnKey, void* value) {
      return value != nullptr && value == this.get(rowKey, columnKey));
   }

    bool removeMapping(void* rowKey, void* columnKey, void* value) {
      if (this.containsMapping(rowKey, columnKey, value)) {
         this.remove(rowKey, columnKey);
    return true;
      } else {
    return false;
      }
   }

   public Set<Cell<R, C, V>> cellSet() {
      return super.cellSet();
   }

   Iterator<Cell<R, C, V>> cellIterator() {
      return std::make_shared<CellIterator>(this, nullptr);
   }

   public Map<C, V> row(R rowKey) {
      return std::make_shared<Row>(this, rowKey);
   }

   public Map<R, V> column(C columnKey) {
      return std::make_shared<Column>(this, columnKey);
   }

   public Set<R> rowKeySet() {
      return this.rowMap().keySet();
   }

   public Set<C> columnKeySet() {
      Set<C> result = this.columnKeySet;
    return result = = nullptr ? (this.columnKeySet = std::make_shared<ColumnKeySet>(this, nullptr)) : result;
   }

   Iterator<C> createColumnKeyIterator() {
      return std::make_shared<ColumnKeyIterator>(this, nullptr);
   }

   public Collection<V> values() {
      return super.values();
   }

   public Map<R, Map<C, V>> rowMap() {
      Map<R, Map<C, V>> result = this.rowMap;
    return result = = nullptr ? (this.rowMap = this.createRowMap()) : result;
   }

   Map<R, Map<C, V>> createRowMap() {
      return std::make_shared<RowMap>(this);
   }

   public Map<C, Map<R, V>> columnMap() {
      StandardTable<R, C, V>.ColumnMap result = this.columnMap;
    return result = = nullptr ? (this.columnMap = std::make_shared<ColumnMap>(this, nullptr)) : result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
