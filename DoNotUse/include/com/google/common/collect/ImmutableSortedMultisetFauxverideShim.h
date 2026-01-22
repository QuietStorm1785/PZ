#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableSortedMultiset/Builder.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMultisetFauxverideShim {
public:
   public static <E> Builder<E> builder() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <E> ImmutableSortedMultiset<E> of(E element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <E> ImmutableSortedMultiset<E> of(E e1, E e2) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <E> ImmutableSortedMultiset<E> of(E e1, E e2, E e3) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <E> ImmutableSortedMultiset<E> of(E e1, E e2, E e3, E e4) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <E> ImmutableSortedMultiset<E> of(E e1, E e2, E e3, E e4, E e5) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <E> ImmutableSortedMultiset<E> of(E e1, E e2, E e3, E e4, E e5, E e6, E... remaining) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public static <E> ImmutableSortedMultiset<E> copyOf(E[] elements) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
