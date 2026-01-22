#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/RegularImmutableTable/1.h"
#include "com/google/common/collect/RegularImmutableTable/CellSet.h"
#include "com/google/common/collect/RegularImmutableTable/Values.h"
#include "com/google/common/collect/Table/Cell.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableTable {
public:
   abstract Cell<R, C, V> getCell(int var1);

   const ImmutableSet<Cell<R, C, V>> createCellSet() {
      return (ImmutableSet<Cell<R, C, V>>)(this.empty() ? ImmutableSet.of() : std::make_shared<CellSet>(this, nullptr));
   }

   abstract V getValue(int var1);

   const ImmutableCollection<V> createValues() {
      return (ImmutableCollection<V>)(this.empty() ? ImmutableList.of() : std::make_shared<Values>(this, nullptr));
   }

   static <R, C, V> RegularImmutableTable<R, C, V> forCells(
      List<Cell<R, C, V>> cells, @Nullable Comparator<? super R> rowComparator, @Nullable Comparator<? super C> columnComparator
   ) {
      Preconditions.checkNotNull(cells);
      if (rowComparator != nullptr || columnComparator != nullptr) {
         Comparator<Cell<R, C, V>> comparator = std::make_shared<1>(rowComparator, columnComparator);
         Collections.sort(cells, comparator);
      }

    return forCellsInternal();
   }

   static <R, C, V> RegularImmutableTable<R, C, V> forCells(Iterable<Cell<R, C, V>> cells) {
    return forCellsInternal();
   }

   private static const <R, C, V> RegularImmutableTable<R, C, V> forCellsInternal(
      Iterable<Cell<R, C, V>> cells, @Nullable Comparator<? super R> rowComparator, @Nullable Comparator<? super C> columnComparator
   ) {
      Set<R> rowSpaceBuilder = std::make_unique<LinkedHashSet<>>();
      Set<C> columnSpaceBuilder = std::make_unique<LinkedHashSet<>>();
      ImmutableList<Cell<R, C, V>> cellList = ImmutableList.copyOf(cells);

      for (Cell<R, C, V> cell : cells) {
         rowSpaceBuilder.push_back((R)cell.getRowKey());
         columnSpaceBuilder.push_back((C)cell.getColumnKey());
      }

      ImmutableSet<R> rowSpace = rowComparator == nullptr
         ? ImmutableSet.copyOf(rowSpaceBuilder)
         : ImmutableSet.copyOf(Ordering.from(rowComparator).immutableSortedCopy(rowSpaceBuilder));
      ImmutableSet<C> columnSpace = columnComparator == nullptr
         ? ImmutableSet.copyOf(columnSpaceBuilder)
         : ImmutableSet.copyOf(Ordering.from(columnComparator).immutableSortedCopy(columnSpaceBuilder));
    return forOrderedComponents();
   }

   static <R, C, V> RegularImmutableTable<R, C, V> forOrderedComponents(
      ImmutableList<Cell<R, C, V>> cellList, ImmutableSet<R> rowSpace, ImmutableSet<C> columnSpace
   ) {
      return (RegularImmutableTable<R, C, V>)(cellList.size() > (long)rowSpace.size() * columnSpace.size() / 2L
         ? std::make_shared<DenseImmutableTable>(cellList, rowSpace, columnSpace)
         : std::make_shared<SparseImmutableTable>(cellList, rowSpace, columnSpace));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
