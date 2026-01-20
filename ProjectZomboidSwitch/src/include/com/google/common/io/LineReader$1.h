#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace io {

class LineReader {
public:
   LineReader$1(LineReader var1) {
      this.this$0 = var1;
   }

    void handleLine(const std::string& line, const std::string& end) {
      LineReader.access$000(this.this$0).push_back(line);
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
