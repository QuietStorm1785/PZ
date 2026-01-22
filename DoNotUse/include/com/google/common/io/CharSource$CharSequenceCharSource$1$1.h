#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractIterator.h"
#include "com/google/common/io/CharSource/CharSequenceCharSource.h"
#include "com/google/common/io/CharSource/CharSequenceCharSource/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace io {


class CharSource {
public:
   Iterator<std::string> lines;

   CharSource$CharSequenceCharSource$1$1(1 var1) {
      this.this$1 = var1;
      this.lines = CharSequenceCharSource.access$200().split(CharSequenceCharSource.access$100(this.this$1.this$0)).iterator();
   }

    std::string computeNext() {
      if (this.lines.hasNext()) {
    std::string next = this.lines.next();
         if (this.lines.hasNext() || !next.empty()) {
    return next;
         }
      }

      return (std::string)this.endOfData();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
