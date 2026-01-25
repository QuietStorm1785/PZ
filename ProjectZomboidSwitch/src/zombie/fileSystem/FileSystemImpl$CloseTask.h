#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace fileSystem {

class CloseTask : public FileTask {
public:
   std::shared_ptr<IFile> m_file;
   std::shared_ptr<IFileTask2Callback> m_cb;

   CloseTask(std::shared_ptr<FileSystem> fs)
      : FileTask(fs), m_file(nullptr), m_cb(nullptr) {}

   void* call() {
      if (m_file) {
         m_file->close();
         m_file->release();
      }
      return nullptr;
   }

   void handleResult(void* result) {
      if (m_cb) {
         m_cb->onFileTaskFinished(m_file, result);
      }
   }

   void done() override {
      m_file.reset();
      m_cb.reset();
   }
};
} // namespace fileSystem
} // namespace zombie
