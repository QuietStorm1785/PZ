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


class CommonMatcher {
public:
   abstract boolean matches();

   abstract boolean find();

   abstract boolean find(int var1);

   abstract std::string replaceAll(std::string var1);

   abstract int end();

   abstract int start();
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
