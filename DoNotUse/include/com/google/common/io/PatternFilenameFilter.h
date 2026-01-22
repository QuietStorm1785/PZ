#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class PatternFilenameFilter {
public:
    const Pattern pattern;

    public PatternFilenameFilter(const std::string& patternStr) {
      this(Pattern.compile(patternStr));
   }

    public PatternFilenameFilter(Pattern pattern) {
      this.pattern = (Pattern)Preconditions.checkNotNull(pattern);
   }

    bool accept(@Nullable File, const std::string& fileName) {
      return this.pattern.matcher(fileName).matches();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
