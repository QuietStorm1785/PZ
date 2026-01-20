#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace collect {

enum class SortedLists {
   NEXT_LOWER,
   NEXT_HIGHER,
   INVERTED_INSERTION_INDEX;

   private SortedLists$KeyAbsentBehavior() {
   }

   abstract int resultIndex(int var1);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
