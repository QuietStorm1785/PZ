#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
    bool hasNext() {
    return false;
   }

    void* next() {
      throw std::make_unique<NoSuchElementException>();
   }

    void remove() {
      CollectPreconditions.checkRemove(false);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
