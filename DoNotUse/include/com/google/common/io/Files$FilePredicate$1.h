#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


enum class Files {
    bool apply(File file) {
      return file.isDirectory();
   }

    std::string toString() {
      return "Files.isDirectory()";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
