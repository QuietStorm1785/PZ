#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class AllEqualOrdering : public Ordering {
public:
    static const AllEqualOrdering INSTANCE = std::make_shared<AllEqualOrdering>();
    static const long serialVersionUID = 0L;

    int compare(@Nullable Object, @Nullable Object) {
    return 0;
   }

   public <E> List<E> sortedCopy(Iterable<E> iterable) {
      return Lists.newArrayList(iterable);
   }

   public <E> ImmutableList<E> immutableSortedCopy(Iterable<E> iterable) {
      return ImmutableList.copyOf(iterable);
   }

   public <S> Ordering<S> reverse() {
    return this;
   }

    void* readResolve() {
    return INSTANCE;
   }

    std::string toString() {
      return "Ordering.allEqual()";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
