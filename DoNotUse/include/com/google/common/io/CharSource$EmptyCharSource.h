#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/io/CharSource/CharSequenceCharSource.h"

namespace com {
namespace google {
namespace common {
namespace io {


class CharSource {
public:
   private static const CharSource$EmptyCharSource INSTANCE = new CharSource$EmptyCharSource();

   private CharSource$EmptyCharSource() {
      super("");
   }

    std::string toString() {
      return "CharSource.empty()";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
