#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Splitter/2.h"
#include "com/google/common/base/Splitter/SplittingIterator.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Splitter {
public:
   Splitter$2$1(2 var1, Splitter x0, CharSequence x1) {
      super(x0, x1);
      this.this$0 = var1;
   }

    int separatorStart(int start) {
    int separatorLength = this.this$0.val$separator.length();
    int p = start;

      label24:
      for (int last = this.toSplit.length() - separatorLength; p <= last; p++) {
         for (int i = 0; i < separatorLength; i++) {
            if (this.toSplit.charAt(i + p) != this.this$0.val$separator.charAt(i)) {
    continue label24;
            }
         }

    return p;
      }

      return -1;
   }

    int separatorEnd(int separatorPosition) {
      return separatorPosition + this.this$0.val$separator.length();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
