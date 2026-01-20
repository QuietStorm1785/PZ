#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Lists.h"

namespace com {
namespace google {
namespace common {
namespace io {


class Files {
public:
   const List<std::string> result = Lists.newArrayList();

    bool processLine(const std::string& line) {
      this.result.push_back(line);
    return true;
   }

   public List<std::string> getResult() {
      return this.result;
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
