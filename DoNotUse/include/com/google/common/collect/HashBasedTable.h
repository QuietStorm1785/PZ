#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/HashBasedTable/Factory.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBasedTable {
public:
    static const long serialVersionUID = 0L;

   public static <R, C, V> HashBasedTable<R, C, V> create() {
      return new HashBasedTable<>(std::make_unique<LinkedHashMap<>>(), std::make_shared<Factory>(0));
   }

   public static <R, C, V> HashBasedTable<R, C, V> create(int expectedRows, int expectedCellsPerRow) {
      CollectPreconditions.checkNonnegative(expectedCellsPerRow, "expectedCellsPerRow");
      Map<R, Map<C, V>> backingMap = Maps.newLinkedHashMapWithExpectedSize(expectedRows);
      return new HashBasedTable<>(backingMap, std::make_shared<Factory>(expectedCellsPerRow));
   }

   public static <R, C, V> HashBasedTable<R, C, V> create(Table<? : public R, ? : public C, ? : public V> table) {
      HashBasedTable<R, C, V> result = create();
      result.putAll(table);
    return result;
   }

   HashBasedTable(Map<R, Map<C, V>> backingMap, Factory<C, V> factory) {
      super(backingMap, factory);
   }

    bool contains(@Nullable Object, @Nullable Object) {
      return super.contains(rowKey, columnKey);
   }

    bool containsColumn(@Nullable Object) {
      return super.containsColumn(columnKey);
   }

    bool containsRow(@Nullable Object) {
      return super.containsRow(rowKey);
   }

    bool containsValue(@Nullable Object) {
      return super.containsValue(value);
   }

    V get(@Nullable Object, @Nullable Object) {
      return (V)super.get(rowKey, columnKey);
   }

    bool equals(@Nullable Object) {
      return super == obj);
   }

    V remove(@Nullable Object, @Nullable Object) {
      return (V)super.remove(rowKey, columnKey);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
