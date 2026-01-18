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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FileTask {
public:
 const FileSystem m_file_system;
 const IFileTaskCallback m_cb;
 int m_priority = 5;

 public FileTask(FileSystem fileSystem) {
 this->m_file_system = fileSystem;
 this->m_cb = nullptr;
 }

 public FileTask(FileSystem fileSystem, IFileTaskCallback cb) {
 this->m_file_system = fileSystem;
 this->m_cb = cb;
 }

 void handleResult(void* result) {
 if (this->m_cb != nullptr) {
 this->m_cb.onFileTaskFinished(result);
 }
 }

 void setPriority(int priority) {
 this->m_priority = priority;
 }

 public void done();

 std::string getErrorMessage() {
 return nullptr;
 }
}
} // namespace fileSystem
} // namespace zombie
