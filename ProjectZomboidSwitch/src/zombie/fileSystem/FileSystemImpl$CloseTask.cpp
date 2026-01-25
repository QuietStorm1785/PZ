#include "zombie/fileSystem/FileSystemImpl$CloseTask.h"

namespace zombie {
namespace fileSystem {

void* FileSystemImpl$CloseTask::call() {
    m_file->close();
    m_file->release();
    return nullptr;
}
}

void FileSystemImpl$CloseTask::handleResult(void* var1) {
    if (m_cb) {
        m_cb->onFileTaskFinished(m_file, var1);
    }
}
}

void FileSystemImpl$CloseTask::done() {
    m_file = nullptr;
    m_cb = nullptr;
}
}

} // namespace fileSystem
} // namespace zombie
