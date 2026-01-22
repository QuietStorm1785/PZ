#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Predicates/ContainsPatternPredicate.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Predicates {
public:
    static const long serialVersionUID = 0L;

   Predicates$ContainsPatternFromStringPredicate(std::string string) {
      super(Platform.compilePattern(string));
   }

    std::string toString() {
      return "Predicates.containsPattern(" + this.pattern.pattern() + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
