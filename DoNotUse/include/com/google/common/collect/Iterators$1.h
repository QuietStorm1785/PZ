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


class Iterators {
public:
    bool hasNext() {
    return false;
   }

    void* next() {
      throw std::make_unique<NoSuchElementException>();
   }

    bool hasPrevious() {
    return false;
   }

    void* previous() {
      throw std::make_unique<NoSuchElementException>();
   }

    int nextIndex() {
    return 0;
   }

    int previousIndex() {
      return -1;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
