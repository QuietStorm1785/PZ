#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace base {


class CommonPattern {
public:
   abstract CommonMatcher matcher(CharSequence var1);

   abstract std::string pattern();

   abstract int flags();

   public abstract std::string toString();

   public abstract int hashCode();

   public abstract boolean equals(Object var1);
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
