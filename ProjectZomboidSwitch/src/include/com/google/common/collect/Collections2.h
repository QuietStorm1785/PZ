#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Joiner.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Collections2/1.h"
#include "com/google/common/collect/Collections2/FilteredCollection.h"
#include "com/google/common/collect/Collections2/OrderedPermutationCollection.h"
#include "com/google/common/collect/Collections2/PermutationCollection.h"
#include "com/google/common/collect/Collections2/TransformedCollection.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Collections2 {
public:
    static const Joiner STANDARD_JOINER = Joiner.on(", ").useForNull("nullptr");

    private Collections2() {
   }

   public static <E> Collection<E> filter(Collection<E> unfiltered, Predicate<? super E> predicate) {
      return dynamic_cast<FilteredCollection*>(unfiltered) != nullptr
         ? ((FilteredCollection)unfiltered).createCombined(predicate)
         : std::make_shared<FilteredCollection>((Collection)Preconditions.checkNotNull(unfiltered), (Predicate)Preconditions.checkNotNull(predicate));
   }

    static bool safeContains(Collection<?> collection, @Nullable Object) {
      Preconditions.checkNotNull(collection);

      try {
         return collection.contains(object);
      } catch (ClassCastException var3) {
    return false;
      } catch (NullPointerException var4) {
    return false;
      }
   }

    static bool safeRemove(Collection<?> collection, @Nullable Object) {
      Preconditions.checkNotNull(collection);

      try {
         return collection.remove(object);
      } catch (ClassCastException var3) {
    return false;
      } catch (NullPointerException var4) {
    return false;
      }
   }

   public static <F, T> Collection<T> transform(Collection<F> fromCollection, Function<? super F, T> function) {
      return std::make_shared<TransformedCollection>(fromCollection, function);
   }

    static bool containsAllImpl(Collection<?> self, Collection<?> c) {
      return Iterables.all(c, Predicates.in(self));
   }

    static std::string toStringImpl(Collection<?> collection) {
    std::stringstream sb = newStringBuilderForCollection(collection.size()).append('[');
      STANDARD_JOINER.appendTo(sb, Iterables.transform(collection, std::make_shared<1>(collection)));
      return sb.append(']');
   }

    static std::stringstream newStringBuilderForCollection(int size) {
      CollectPreconditions.checkNonnegative(size, "size");
      return new std::stringstream((int)Math.min(size * 8L, 1073741824L));
   }

   static <T> Collection<T> cast(Iterable<T> iterable) {
      return (Collection<T>)iterable;
   }

   public static <E : public Comparable<? super E>> Collection<List<E>> orderedPermutations(Iterable<E> elements) {
    return orderedPermutations();
   }

   public static <E> Collection<List<E>> orderedPermutations(Iterable<E> elements, Comparator<? super E> comparator) {
      return std::make_shared<OrderedPermutationCollection>(elements, comparator);
   }

   public static <E> Collection<List<E>> permutations(Collection<E> elements) {
      return std::make_shared<PermutationCollection>(ImmutableList.copyOf(elements));
   }

    static bool isPermutation(List<?> first, List<?> second) {
      if (first.size() != second.size()) {
    return false;
      } else {
         Multiset<?> firstMultiset = HashMultiset.create(first);
         Multiset<?> secondMultiset = HashMultiset.create(second);
         return firstMultiset == secondMultiset);
      }
   }

    static bool isPositiveInt(long n) {
      return n >= 0L && n <= 2147483647L;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
