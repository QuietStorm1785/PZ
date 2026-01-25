#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace fileSystem {

class OpenTask : public FileTask {
public:
   std::shared_ptr<IFile> m_file;
   std::string m_path;
   int m_mode;
   std::shared_ptr<IFileTask2Callback> m_cb;

   OpenTask(std::shared_ptr<FileSystem> fs)
      : FileTask(fs), m_file(nullptr), m_path(), m_mode(0), m_cb(nullptr) {}

   void* call() {
      if (m_file)
         return reinterpret_cast<void*>(m_file->open(m_path, m_mode));
      return nullptr;
   }

   void handleResult(void* result) {
      if (m_cb) {
         m_cb->onFileTaskFinished(m_file, result);
      }
   }

   void done() override {
      if ((m_mode & 5) == 5 && m_fileSystem) {
         // Assuming FileSystem has closeAsync method
         m_fileSystem->closeAsync(m_file, nullptr);
      }
      m_file.reset();
      m_path.clear();
      m_cb.reset();
   }
};
} // namespace fileSystem
} // namespace zombie
