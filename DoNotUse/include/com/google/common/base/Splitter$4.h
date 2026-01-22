#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Splitter/4/1.h"
#include "com/google/common/base/Splitter/SplittingIterator.h"
#include "com/google/common/base/Splitter/Strategy.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Splitter {
public:
   Splitter$4(int var1) {
      this.val$length = var1;
   }

    SplittingIterator iterator(Splitter splitter, CharSequence toSplit) {
      return std::make_shared<1>(this, splitter, toSplit);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
