#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace asset {


class FileTask_Exists : public FileTask {
public:
    std::string fileName;

    public FileTask_Exists(const std::string& var1, IFileTaskCallback var2, FileSystem var3) {
      super(var3, var2);
      this.fileName = var1;
   }

    void done() {
   }

    void* call() {
      return new File(this.fileName).exists();
   }
}
} // namespace asset
} // namespace zombie
