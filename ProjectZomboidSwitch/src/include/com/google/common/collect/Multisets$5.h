#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/primitives/Ints.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
    int compare(Entry<?> entry1, Entry<?> entry2) {
      return Ints.compare(entry2.getCount(), entry1.getCount());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
