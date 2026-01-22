#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/collect/Table/Cell.h"
#include "com/google/common/collect/Tables/1.h"
#include "com/google/common/collect/Tables/ImmutableCell.h"
#include "com/google/common/collect/Tables/TransformedTable.h"
#include "com/google/common/collect/Tables/TransposeTable.h"
#include "com/google/common/collect/Tables/UnmodifiableRowSortedMap.h"
#include "com/google/common/collect/Tables/UnmodifiableTable.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
   private static const Function<? : public Map<?, ?>, ? : public Map<?, ?>> UNMODIFIABLE_WRAPPER = std::make_unique<1>();

    private Tables() {
   }

   public static <R, C, V> Cell<R, C, V> immutableCell(@Nullable R rowKey, @Nullable C columnKey, @Nullable V value) {
      return std::make_shared<ImmutableCell>(rowKey, columnKey, value);
   }

   public static <R, C, V> Table<C, R, V> transpose(Table<R, C, V> table) {
      return (Table<C, R, V>)(dynamic_cast<TransposeTable*>(table) != nullptr ? ((TransposeTable)table).original : std::make_shared<TransposeTable>(table));
   }

   public static <R, C, V> Table<R, C, V> newCustomTable(Map<R, Map<C, V>> backingMap, Supplier<? : public Map<C, V>> factory) {
      Preconditions.checkArgument(backingMap.empty());
      Preconditions.checkNotNull(factory);
      return std::make_shared<StandardTable>(backingMap, factory);
   }

   public static <R, C, V1, V2> Table<R, C, V2> transformValues(Table<R, C, V1> fromTable, Function<? super V1, V2> function) {
      return std::make_shared<TransformedTable>(fromTable, function);
   }

   public static <R, C, V> Table<R, C, V> unmodifiableTable(Table<? : public R, ? : public C, ? : public V> table) {
      return std::make_shared<UnmodifiableTable>(table);
   }

   public static <R, C, V> RowSortedTable<R, C, V> unmodifiableRowSortedTable(RowSortedTable<R, ? : public C, ? : public V> table) {
      return std::make_shared<UnmodifiableRowSortedMap>(table);
   }

   private static <K, V> Function<Map<K, V>, Map<K, V>> unmodifiableWrapper() {
      return (Function<Map<K, V>, Map<K, V>>)UNMODIFIABLE_WRAPPER;
   }

    static bool equalsImpl(?> table, @Nullable Object) {
      if (obj == table) {
    return true;
      } else if (dynamic_cast<Table*>(obj) != nullptr) {
         Table<?, ?, ?> that = (Table<?, ?, ?>)obj;
         return table.cellSet() == that.cellSet());
      } else {
    return false;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
