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
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
   const Table<? : public R, ? : public C, ? : public V> delegate;
    static const long serialVersionUID = 0L;

   Tables$UnmodifiableTable(Table<? : public R, ? : public C, ? : public V> delegate) {
      this.delegate = (Table<? : public R, ? : public C, ? : public V>)Preconditions.checkNotNull(delegate);
   }

   protected Table<R, C, V> delegate() {
      return (Table<R, C, V>)this.delegate;
   }

   public Set<Cell<R, C, V>> cellSet() {
      return Collections.unmodifiableSet(super.cellSet());
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Map<R, V> column(@Nullable C columnKey) {
      return Collections.unmodifiableMap(super.column(columnKey));
   }

   public Set<C> columnKeySet() {
      return Collections.unmodifiableSet(super.columnKeySet());
   }

   public Map<C, Map<R, V>> columnMap() {
      Function<Map<R, V>, Map<R, V>> wrapper = Tables.access$000();
      return Collections.unmodifiableMap(Maps.transformValues(super.columnMap(), wrapper));
   }

    V put(@Nullable R, @Nullable C, @Nullable V) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Table<? extends, ? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V remove(@Nullable Object, @Nullable Object) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Map<C, V> row(@Nullable R rowKey) {
      return Collections.unmodifiableMap(super.row(rowKey));
   }

   public Set<R> rowKeySet() {
      return Collections.unmodifiableSet(super.rowKeySet());
   }

   public Map<R, Map<C, V>> rowMap() {
      Function<Map<C, V>, Map<C, V>> wrapper = Tables.access$000();
      return Collections.unmodifiableMap(Maps.transformValues(super.rowMap(), wrapper));
   }

   public Collection<V> values() {
      return Collections.unmodifiableCollection(super.values());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
