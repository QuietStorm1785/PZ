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
    IFileTask2Callback m_cb;

   FileSystemImpl$CloseTask(FileSystem var1) {
      super(var1);
   }

    void* call() {
      this.m_file.close();
      this.m_file.release();
    return nullptr;
   }

    void handleResult(void* var1) {
      if (this.m_cb != nullptr) {
         this.m_cb.onFileTaskFinished(this.m_file, var1);
      }
   }

    void done() {
      this.m_file = nullptr;
      this.m_cb = nullptr;
   }
}
} // namespace fileSystem
} // namespace zombie
