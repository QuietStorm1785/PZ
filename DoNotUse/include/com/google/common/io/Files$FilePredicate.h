#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


enum class Files {
   IS_DIRECTORY,
   IS_FILE;

   private Files$FilePredicate() {
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
