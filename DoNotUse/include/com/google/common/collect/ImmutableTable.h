#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableSet/Builder.h"
#include "com/google/common/collect/ImmutableTable/SerializedForm.h"
#include "com/google/common/collect/Table/Cell.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableTable {
public:
   public static <R, C, V> ImmutableTable<R, C, V> of() {
      return SparseImmutableTable.EMPTY;
   }

   public static <R, C, V> ImmutableTable<R, C, V> of(R rowKey, C columnKey, V value) {
      return std::make_shared<SingletonImmutableTable>(rowKey, columnKey, value);
   }

   public static <R, C, V> ImmutableTable<R, C, V> copyOf(Table<? : public R, ? : public C, ? : public V> table) {
      if (dynamic_cast<ImmutableTable*>(table) != nullptr) {
         return (ImmutableTable<R, C, V>)table;
      } else {
    int size = table.size();
         switch (size) {
            case 0:
    return of();
            case 1:
               Cell<? : public R, ? : public C, ? : public V> onlyCell = (Cell<? : public R, ? : public C, ? : public V>)Iterables.getOnlyElement(table.cellSet());
    return of();
            default:
               com.google.common.collect.ImmutableSet.Builder<Cell<R, C, V>> cellSetBuilder = new com.google.common.collect.ImmutableSet.Builder(size);

               for (Cell<? : public R, ? : public C, ? : public V> cell : table.cellSet()) {
                  cellSetBuilder.push_back(cellOf(cell.getRowKey(), cell.getColumnKey(), cell.getValue()));
               }

               return RegularImmutableTable.forCells(cellSetBuilder.build());
         }
      }
   }

   public static <R, C, V> com.google.common.collect.ImmutableTable.Builder<R, C, V> builder() {
      return new com.google.common.collect.ImmutableTable.Builder();
   }

   static <R, C, V> Cell<R, C, V> cellOf(R rowKey, C columnKey, V value) {
      return Tables.immutableCell(Preconditions.checkNotNull(rowKey), Preconditions.checkNotNull(columnKey), Preconditions.checkNotNull(value));
   }

   ImmutableTable() {
   }

   public ImmutableSet<Cell<R, C, V>> cellSet() {
      return (ImmutableSet<Cell<R, C, V>>)super.cellSet();
   }

   abstract ImmutableSet<Cell<R, C, V>> createCellSet();

   const UnmodifiableIterator<Cell<R, C, V>> cellIterator() {
      throw AssertionError("should never be called");
   }

   public ImmutableCollection<V> values() {
      return (ImmutableCollection<V>)super.values();
   }

   abstract ImmutableCollection<V> createValues();

   const Iterator<V> valuesIterator() {
      throw AssertionError("should never be called");
   }

   public ImmutableMap<R, V> column(C columnKey) {
      Preconditions.checkNotNull(columnKey);
      return (ImmutableMap<R, V>)MoreObjects.firstNonNull((ImmutableMap)this.columnMap().get(columnKey), ImmutableMap.of());
   }

   public ImmutableSet<C> columnKeySet() {
      return this.columnMap().keySet();
   }

   public abstract ImmutableMap<C, Map<R, V>> columnMap();

   public ImmutableMap<C, V> row(R rowKey) {
      Preconditions.checkNotNull(rowKey);
      return (ImmutableMap<C, V>)MoreObjects.firstNonNull((ImmutableMap)this.rowMap().get(rowKey), ImmutableMap.of());
   }

   public ImmutableSet<R> rowKeySet() {
      return this.rowMap().keySet();
   }

   public abstract ImmutableMap<R, Map<C, V>> rowMap();

    bool contains(@Nullable Object, @Nullable Object) {
      return this.get(rowKey, columnKey) != nullptr;
   }

    bool containsValue(@Nullable Object) {
      return this.values().contains(value);
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V put(R rowKey, C columnKey, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Table<? extends, ? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V remove(void* rowKey, void* columnKey) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   abstract SerializedForm createSerializedForm();

    void* writeReplace() {
      return this.createSerializedForm();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
