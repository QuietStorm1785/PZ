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
   std::shared_ptr<FileSystem> m_fileSystem;
   std::shared_ptr<IFileTaskCallback> m_callback;
   int m_priority = 5;
   std::string m_errorMessage;

   FileTask(std::shared_ptr<FileSystem> fs)
      : m_fileSystem(std::move(fs)), m_callback(nullptr), m_priority(5), m_errorMessage("") {}

   FileTask(std::shared_ptr<FileSystem> fs, std::shared_ptr<IFileTaskCallback> cb)
      : m_fileSystem(std::move(fs)), m_callback(std::move(cb)), m_priority(5), m_errorMessage("") {}

   virtual ~FileTask() = default;

   virtual void done() = 0;

   void handleResult(void* result) {
      if (m_callback) {
         m_callback->onFileTaskFinished(result);
      }
   }

   void setPriority(int priority) {
      m_priority = priority;
   }

   std::string getErrorMessage() const {
      return m_errorMessage;
   }
};
} // namespace fileSystem
} // namespace zombie
