#include <string>
#include "zombie/fileSystem/FileTask.h"

namespace zombie {
namespace fileSystem {


FileTask::FileTask(FileSystem var1)
    : m_fileSystem(var1), m_callback(nullptr), m_priority(0), m_errorMessage("") {}


FileTask::FileTask(FileSystem var1, IFileTaskCallback var2)
    : m_fileSystem(var1), m_callback(var2), m_priority(0), m_errorMessage("") {}


void FileTask::handleResult(void* var1) {
    // If callback is set, call it with the result
    if (m_callback) {
        m_callback->onResult(var1);
    }
}


void FileTask::setPriority(int var1) {
    m_priority = var1;
}


std::string FileTask::getErrorMessage() {
    return m_errorMessage;
}

} // namespace fileSystem
} // namespace zombie
