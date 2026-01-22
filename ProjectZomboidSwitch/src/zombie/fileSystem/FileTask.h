#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace fileSystem {


class FileTask {
public:
    const FileSystem m_file_system;
    const IFileTaskCallback m_cb;
    int m_priority = 5;

    public FileTask(FileSystem var1) {
      this.m_file_system = var1;
      this.m_cb = nullptr;
   }

    public FileTask(FileSystem var1, IFileTaskCallback var2) {
      this.m_file_system = var1;
      this.m_cb = var2;
   }

    void handleResult(void* var1) {
      if (this.m_cb != nullptr) {
         this.m_cb.onFileTaskFinished(var1);
      }
   }

    void setPriority(int var1) {
      this.m_priority = var1;
   }

   public abstract void done();

    std::string getErrorMessage() {
    return nullptr;
   }
}
} // namespace fileSystem
} // namespace zombie
