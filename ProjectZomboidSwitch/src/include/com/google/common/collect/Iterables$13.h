#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterables {
public:
   public Iterator<? : public T> apply(Iterable<? : public T> iterable) {
      return iterable.iterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
