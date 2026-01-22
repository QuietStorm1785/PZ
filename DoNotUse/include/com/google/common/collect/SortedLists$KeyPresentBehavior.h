#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


enum class SortedLists {
   ANY_PRESENT,
   LAST_PRESENT,
   FIRST_PRESENT,
   FIRST_AFTER,
   LAST_BEFORE;

   private SortedLists$KeyPresentBehavior() {
   }

   abstract <E> int resultIndex(Comparator<? super E> var1, E var2, List<? : public E> var3, int var4);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
