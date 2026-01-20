#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Table/Cell.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingTable {
public:
    protected ForwardingTable() {
   }

   protected abstract Table<R, C, V> delegate();

   public Set<Cell<R, C, V>> cellSet() {
      return this.delegate().cellSet();
   }

    void clear() {
      this.delegate().clear();
   }

   public Map<R, V> column(C columnKey) {
      return this.delegate().column(columnKey);
   }

   public Set<C> columnKeySet() {
      return this.delegate().columnKeySet();
   }

   public Map<C, Map<R, V>> columnMap() {
      return this.delegate().columnMap();
   }

    bool contains(void* rowKey, void* columnKey) {
      return this.delegate().contains(rowKey, columnKey);
   }

    bool containsColumn(void* columnKey) {
      return this.delegate().containsColumn(columnKey);
   }

    bool containsRow(void* rowKey) {
      return this.delegate().containsRow(rowKey);
   }

    bool containsValue(void* value) {
      return this.delegate().containsValue(value);
   }

    V get(void* rowKey, void* columnKey) {
      return (V)this.delegate().get(rowKey, columnKey);
   }

    bool isEmpty() {
      return this.delegate().empty();
   }

    V put(R rowKey, C columnKey, V value) {
      return (V)this.delegate().put(rowKey, columnKey, value);
   }

    void putAll(Table<? extends, ? extends, ? extends) {
      this.delegate().putAll(table);
   }

    V remove(void* rowKey, void* columnKey) {
      return (V)this.delegate().remove(rowKey, columnKey);
   }

   public Map<C, V> row(R rowKey) {
      return this.delegate().row(rowKey);
   }

   public Set<R> rowKeySet() {
      return this.delegate().rowKeySet();
   }

   public Map<R, Map<C, V>> rowMap() {
      return this.delegate().rowMap();
   }

    int size() {
      return this.delegate().size();
   }

   public Collection<V> values() {
      return this.delegate().values();
   }

    bool equals(void* obj) {
    return obj = = this || this.delegate() == obj);
   }

    int hashCode() {
      return this.delegate().hashCode();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
