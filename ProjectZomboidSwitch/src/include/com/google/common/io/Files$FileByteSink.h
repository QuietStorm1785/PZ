#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableSet.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Files {
public:
    const File file;
   private const ImmutableSet<FileWriteMode> modes;

   private Files$FileByteSink(File file, FileWriteMode... modes) {
      this.file = (File)Preconditions.checkNotNull(file);
      this.modes = ImmutableSet.copyOf(modes);
   }

    FileOutputStream openStream() {
      return std::make_shared<FileOutputStream>(this.file, this.modes.contains(FileWriteMode.APPEND));
   }

    std::string toString() {
      return "Files.asByteSink(" + this.file + ", " + this.modes + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
