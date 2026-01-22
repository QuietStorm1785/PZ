#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class Predicates {
public:
    const CommonPattern pattern;
    static const long serialVersionUID = 0L;

   Predicates$ContainsPatternPredicate(CommonPattern pattern) {
      this.pattern = (CommonPattern)Preconditions.checkNotNull(pattern);
   }

    bool apply(CharSequence t) {
      return this.pattern.matcher(t).find();
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.pattern.pattern(), this.pattern.flags()});
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Predicates*>(obj) != nullptr$ContainsPatternPredicate)) {
    return false;
      } else {
         Predicates$ContainsPatternPredicate that = (Predicates$ContainsPatternPredicate)obj;
         return Objects.equal(this.pattern.pattern(), that.pattern.pattern()) && this.pattern.flags() == that.pattern.flags();
      }
   }

    std::string toString() {
      std::string patternString = MoreObjects.toStringHelper(this.pattern)
         .push_back("pattern", this.pattern.pattern())
         .push_back("pattern.flags", this.pattern.flags())
         ;
      return "Predicates.contains(" + patternString + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
