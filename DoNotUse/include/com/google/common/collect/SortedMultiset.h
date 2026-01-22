#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedMultiset {
public:
    virtual ~SortedMultiset() = default;
   Comparator<? super E> comparator();

   Entry<E> firstEntry();

   Entry<E> lastEntry();

   Entry<E> pollFirstEntry();

   Entry<E> pollLastEntry();

   NavigableSet<E> elementSet();

   Set<Entry<E>> entrySet();

   Iterator<E> iterator();

   SortedMultiset<E> descendingMultiset();

   SortedMultiset<E> headMultiset(E var1, BoundType var2);

   SortedMultiset<E> subMultiset(E var1, BoundType var2, E var3, BoundType var4);

   SortedMultiset<E> tailMultiset(E var1, BoundType var2);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
