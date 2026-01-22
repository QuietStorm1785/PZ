#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace fileSystem {

class FileSystemImpl {
public:
    IFile m_file;
    std::string m_path;
    int m_mode;
    IFileTask2Callback m_cb;

   FileSystemImpl$OpenTask(FileSystem var1) {
      super(var1);
   }

    void* call() {
      return this.m_file.open(this.m_path, this.m_mode);
   }

    void handleResult(void* var1) {
      if (this.m_cb != nullptr) {
         this.m_cb.onFileTaskFinished(this.m_file, var1);
      }
   }

    void done() {
      if ((this.m_mode & 5) == 5) {
         this.m_file_system.closeAsync(this.m_file, nullptr);
      }

      this.m_file = nullptr;
      this.m_path = nullptr;
      this.m_cb = nullptr;
   }
}
} // namespace fileSystem
} // namespace zombie
