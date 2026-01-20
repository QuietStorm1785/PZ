#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeTraverser.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Files {
public:
   public Iterable<File> children(File file) {
      if (file.isDirectory()) {
         File[] files = file.listFiles();
         if (files != nullptr) {
            return Collections.unmodifiableList(Arrays.asList(files));
         }
      }

      return Collections.emptyList();
   }

    std::string toString() {
      return "Files.fileTreeTraverser()";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
