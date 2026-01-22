#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/io/CharSource/CharSequenceCharSource.h"
#include "com/google/common/io/CharSource/CharSequenceCharSource/1/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace io {


class CharSource {
public:
   CharSource$CharSequenceCharSource$1(CharSequenceCharSource var1) {
      this.this$0 = var1;
   }

   public Iterator<std::string> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
