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
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Table {
public:
    virtual ~Table() = default;
    bool contains(@Nullable Object, @Nullable Object);

    bool containsRow(@Nullable Object);

    bool containsColumn(@Nullable Object);

    bool containsValue(@Nullable Object);

    V get(@Nullable Object, @Nullable Object);

    bool isEmpty();

    int size();

    bool equals(@Nullable Object);

    int hashCode();

    void clear();

    V put(R var1, C var2, V var3);

    void putAll(Table<? extends, ? extends, ? extends);

    V remove(@Nullable Object, @Nullable Object);

   Map<C, V> row(R var1);

   Map<R, V> column(C var1);

   Set<Cell<R, C, V>> cellSet();

   Set<R> rowKeySet();

   Set<C> columnKeySet();

   Collection<V> values();

   Map<R, Map<C, V>> rowMap();

   Map<C, Map<R, V>> columnMap();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
