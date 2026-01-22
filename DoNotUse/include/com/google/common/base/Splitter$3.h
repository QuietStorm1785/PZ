#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Splitter/3/1.h"
#include "com/google/common/base/Splitter/SplittingIterator.h"
#include "com/google/common/base/Splitter/Strategy.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Splitter {
public:
   Splitter$3(CommonPattern var1) {
      this.val$separatorPattern = var1;
   }

    SplittingIterator iterator(Splitter splitter, CharSequence toSplit) {
    CommonMatcher matcher = this.val$separatorPattern.matcher(toSplit);
      return std::make_shared<1>(this, splitter, toSplit, matcher);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
