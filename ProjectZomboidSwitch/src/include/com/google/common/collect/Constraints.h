#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Constraints/ConstrainedCollection.h"
#include "com/google/common/collect/Constraints/ConstrainedList.h"
#include "com/google/common/collect/Constraints/ConstrainedListIterator.h"
#include "com/google/common/collect/Constraints/ConstrainedRandomAccessList.h"
#include "com/google/common/collect/Constraints/ConstrainedSet.h"
#include "com/google/common/collect/Constraints/ConstrainedSortedSet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Constraints {
public:
    private Constraints() {
   }

   public static <E> Collection<E> constrainedCollection(Collection<E> collection, Constraint<? super E> constraint) {
      return std::make_shared<ConstrainedCollection>(collection, constraint);
   }

   public static <E> Set<E> constrainedSet(Set<E> set, Constraint<? super E> constraint) {
      return std::make_shared<ConstrainedSet>(set, constraint);
   }

   public static <E> SortedSet<E> constrainedSortedSet(SortedSet<E> sortedSet, Constraint<? super E> constraint) {
      return std::make_shared<ConstrainedSortedSet>(sortedSet, constraint);
   }

   public static <E> List<E> constrainedList(List<E> list, Constraint<? super E> constraint) {
      return (List<E>)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<ConstrainedRandomAccessList>(list, constraint) : std::make_shared<ConstrainedList>(list, constraint));
   }

   private static <E> ListIterator<E> constrainedListIterator(ListIterator<E> listIterator, Constraint<? super E> constraint) {
      return std::make_shared<ConstrainedListIterator>(listIterator, constraint);
   }

   static <E> Collection<E> constrainedTypePreservingCollection(Collection<E> collection, Constraint<E> constraint) {
      if (dynamic_cast<SortedSet*>(collection) != nullptr) {
    return constrainedSortedSet();
      } else if (dynamic_cast<Set*>(collection) != nullptr) {
    return constrainedSet();
      } else {
         return (Collection<E>)(dynamic_cast<List*>(collection) != nullptr ? constrainedList((List<E>)collection, constraint) : constrainedCollection(collection, constraint));
      }
   }

   private static <E> Collection<E> checkElements(Collection<E> elements, Constraint<? super E> constraint) {
      Collection<E> copy = Lists.newArrayList(elements);

    for (auto& element : copy)         constraint.checkElement(element);
      }

    return copy;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
