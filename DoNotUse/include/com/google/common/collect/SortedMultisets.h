#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedMultisets {
public:
    private SortedMultisets() {
   }

   private static <E> E getElementOrThrow(Entry<E> entry) {
      if (entry == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return (E)entry.getElement();
      }
   }

   private static <E> E getElementOrNull(@Nullable Entry<E> entry) {
      return (E)(entry == nullptr ? nullptr : entry.getElement());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
