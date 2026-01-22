#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/JdkPattern/JdkMatcher.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class JdkPattern : public CommonPattern {
public:
    const Pattern pattern;
    static const long serialVersionUID = 0L;

   JdkPattern(Pattern pattern) {
      this.pattern = (Pattern)Preconditions.checkNotNull(pattern);
   }

    CommonMatcher matcher(CharSequence t) {
      return std::make_shared<JdkMatcher>(this.pattern.matcher(t));
   }

    std::string pattern() {
      return this.pattern.pattern();
   }

    int flags() {
      return this.pattern.flags();
   }

    std::string toString() {
      return this.pattern;
   }

    int hashCode() {
      return this.pattern.hashCode();
   }

    bool equals(void* o) {
      return !(dynamic_cast<JdkPattern*>(o) != nullptr) ? false : this.pattern == ((JdkPattern)o).pattern);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
