#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/TreeBasedTable/1.h"
#include "com/google/common/collect/TreeBasedTable/2.h"
#include "com/google/common/collect/TreeBasedTable/Factory.h"
#include "com/google/common/collect/TreeBasedTable/TreeRow.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeBasedTable {
public:
   private const Comparator<? super C> columnComparator;
    static const long serialVersionUID = 0L;

   public static <R : public Comparable, C : public Comparable, V> TreeBasedTable<R, C, V> create() {
      return new TreeBasedTable<>(Ordering.natural(), Ordering.natural());
   }

   public static <R, C, V> TreeBasedTable<R, C, V> create(Comparator<? super R> rowComparator, Comparator<? super C> columnComparator) {
      Preconditions.checkNotNull(rowComparator);
      Preconditions.checkNotNull(columnComparator);
      return new TreeBasedTable<>(rowComparator, columnComparator);
   }

   public static <R, C, V> TreeBasedTable<R, C, V> create(TreeBasedTable<R, C, ? : public V> table) {
      TreeBasedTable<R, C, V> result = new TreeBasedTable<>(table.rowComparator(), table.columnComparator());
      result.putAll(table);
    return result;
   }

   TreeBasedTable(Comparator<? super R> rowComparator, Comparator<? super C> columnComparator) {
      super(new std::map<>(rowComparator), std::make_shared<Factory>(columnComparator));
      this.columnComparator = columnComparator;
   }

   public Comparator<? super R> rowComparator() {
      return this.rowKeySet().comparator();
   }

   public Comparator<? super C> columnComparator() {
      return this.columnComparator;
   }

   public SortedMap<C, V> row(R rowKey) {
      return std::make_shared<TreeRow>(this, rowKey);
   }

   public SortedSet<R> rowKeySet() {
      return super.rowKeySet();
   }

   public SortedMap<R, Map<C, V>> rowMap() {
      return super.rowMap();
   }

   Iterator<C> createColumnKeyIterator() {
      Comparator<? super C> comparator = this.columnComparator();
      Iterator<C> merged = Iterators.mergeSorted(Iterables.transform(this.backingMap.values(), std::make_shared<1>(this)), comparator);
      return std::make_shared<2>(this, merged, comparator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
