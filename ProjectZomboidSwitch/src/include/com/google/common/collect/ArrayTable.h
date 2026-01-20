#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ArrayTable/1.h"
#include "com/google/common/collect/ArrayTable/Column.h"
#include "com/google/common/collect/ArrayTable/ColumnMap.h"
#include "com/google/common/collect/ArrayTable/Row.h"
#include "com/google/common/collect/ArrayTable/RowMap.h"
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


class ArrayTable {
public:
   private const ImmutableList<R> rowList;
   private const ImmutableList<C> columnList;
   private const ImmutableMap<R, int> rowKeyToIndex;
   private const ImmutableMap<C, int> columnKeyToIndex;
   private const V[][] array;
   private transient ArrayTable<R, C, V>.ColumnMap columnMap;
   private transient ArrayTable<R, C, V>.RowMap rowMap;
    static const long serialVersionUID = 0L;

   public static <R, C, V> ArrayTable<R, C, V> create(Iterable<? : public R> rowKeys, Iterable<? : public C> columnKeys) {
      return new ArrayTable<>(rowKeys, columnKeys);
   }

   public static <R, C, V> ArrayTable<R, C, V> create(Table<R, C, V> table) {
      return dynamic_cast<ArrayTable*>(table) != nullptr ? new ArrayTable<>((ArrayTable<R, C, V>)table) : new ArrayTable<>(table);
   }

    private ArrayTable(Iterable<? extends, Iterable<? extends) {
      this.rowList = ImmutableList.copyOf(rowKeys);
      this.columnList = ImmutableList.copyOf(columnKeys);
      Preconditions.checkArgument(!this.rowList.empty());
      Preconditions.checkArgument(!this.columnList.empty());
      this.rowKeyToIndex = Maps.indexMap(this.rowList);
      this.columnKeyToIndex = Maps.indexMap(this.columnList);
      V[][] tmpArray = (V[][])(new Object[this.rowList.size()][this.columnList.size()]);
      this.array = tmpArray;
      this.eraseAll();
   }

    private ArrayTable(V> table) {
      this(table.rowKeySet(), table.columnKeySet());
      this.putAll(table);
   }

    private ArrayTable(V> table) {
      this.rowList = table.rowList;
      this.columnList = table.columnList;
      this.rowKeyToIndex = table.rowKeyToIndex;
      this.columnKeyToIndex = table.columnKeyToIndex;
      V[][] copy = (V[][])(new Object[this.rowList.size()][this.columnList.size()]);
      this.array = copy;
      this.eraseAll();

      for (int i = 0; i < this.rowList.size(); i++) {
         System.arraycopy(table.array[i], 0, copy[i], 0, table.array[i].length);
      }
   }

   public ImmutableList<R> rowKeyList() {
      return this.rowList;
   }

   public ImmutableList<C> columnKeyList() {
      return this.columnList;
   }

    V at(int rowIndex, int columnIndex) {
      Preconditions.checkElementIndex(rowIndex, this.rowList.size());
      Preconditions.checkElementIndex(columnIndex, this.columnList.size());
      return this.array[rowIndex][columnIndex];
   }

    V set(int rowIndex, int columnIndex, @Nullable V) {
      Preconditions.checkElementIndex(rowIndex, this.rowList.size());
      Preconditions.checkElementIndex(columnIndex, this.columnList.size());
    V oldValue = this.array[rowIndex][columnIndex];
      this.array[rowIndex][columnIndex] = value;
    return oldValue;
   }

   public V[][] toArray(Class<V> valueClass) {
      V[][] copy = (V[][])((Object[][])Array.newInstance(valueClass, this.rowList.size(), this.columnList.size()));

      for (int i = 0; i < this.rowList.size(); i++) {
         System.arraycopy(this.array[i], 0, copy[i], 0, this.array[i].length);
      }

    return copy;
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void eraseAll() {
      for (V[] row : this.array) {
         Arrays.fill(row, nullptr);
      }
   }

    bool contains(@Nullable Object, @Nullable Object) {
      return this.containsRow(rowKey) && this.containsColumn(columnKey);
   }

    bool containsColumn(@Nullable Object) {
      return this.columnKeyToIndex.containsKey(columnKey);
   }

    bool containsRow(@Nullable Object) {
      return this.rowKeyToIndex.containsKey(rowKey);
   }

    bool containsValue(@Nullable Object) {
      for (V[] row : this.array) {
    for (auto& element : row)            if (Objects.equal(value, element)) {
    return true;
            }
         }
      }

    return false;
   }

    V get(@Nullable Object, @Nullable Object) {
    int rowIndex = (int)this.rowKeyToIndex.get(rowKey);
    int columnIndex = (int)this.columnKeyToIndex.get(columnKey);
      return rowIndex != nullptr && columnIndex != nullptr ? this.at(rowIndex, columnIndex) : nullptr;
   }

    bool isEmpty() {
    return false;
   }

    V put(R rowKey, C columnKey, @Nullable V) {
      Preconditions.checkNotNull(rowKey);
      Preconditions.checkNotNull(columnKey);
    int rowIndex = (int)this.rowKeyToIndex.get(rowKey);
      Preconditions.checkArgument(rowIndex != nullptr, "Row %s not in %s", rowKey, this.rowList);
    int columnIndex = (int)this.columnKeyToIndex.get(columnKey);
      Preconditions.checkArgument(columnIndex != nullptr, "Column %s not in %s", columnKey, this.columnList);
      return this.set(rowIndex, columnIndex, value);
   }

    void putAll(Table<? extends, ? extends, ? extends) {
      super.putAll(table);
   }

    V remove(void* rowKey, void* columnKey) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V erase(@Nullable Object, @Nullable Object) {
    int rowIndex = (int)this.rowKeyToIndex.get(rowKey);
    int columnIndex = (int)this.columnKeyToIndex.get(columnKey);
      return rowIndex != nullptr && columnIndex != nullptr ? this.set(rowIndex, columnIndex, nullptr) : nullptr;
   }

    int size() {
      return this.rowList.size() * this.columnList.size();
   }

   public Set<Cell<R, C, V>> cellSet() {
      return super.cellSet();
   }

   Iterator<Cell<R, C, V>> cellIterator() {
      return std::make_shared<1>(this, this.size());
   }

   public Map<R, V> column(C columnKey) {
      Preconditions.checkNotNull(columnKey);
    int columnIndex = (int)this.columnKeyToIndex.get(columnKey);
      return (Map<R, V>)(columnIndex == nullptr ? ImmutableMap.of() : std::make_shared<Column>(this, columnIndex));
   }

   public ImmutableSet<C> columnKeySet() {
      return this.columnKeyToIndex.keySet();
   }

   public Map<C, Map<R, V>> columnMap() {
      ArrayTable<R, C, V>.ColumnMap map = this.columnMap;
    return map = = nullptr ? (this.columnMap = std::make_shared<ColumnMap>(this, nullptr)) : map;
   }

   public Map<C, V> row(R rowKey) {
      Preconditions.checkNotNull(rowKey);
    int rowIndex = (int)this.rowKeyToIndex.get(rowKey);
      return (Map<C, V>)(rowIndex == nullptr ? ImmutableMap.of() : std::make_shared<Row>(this, rowIndex));
   }

   public ImmutableSet<R> rowKeySet() {
      return this.rowKeyToIndex.keySet();
   }

   public Map<R, Map<C, V>> rowMap() {
      ArrayTable<R, C, V>.RowMap map = this.rowMap;
    return map = = nullptr ? (this.rowMap = std::make_shared<RowMap>(this, nullptr)) : map;
   }

   public Collection<V> values() {
      return super.values();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
