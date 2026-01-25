#include "zombie/fileSystem/FileSystemImpl$OpenTask.h"

namespace zombie {
namespace fileSystem {

void* FileSystemImpl$OpenTask::call() {
    return m_file->open(m_path, m_mode);
}
}

void FileSystemImpl$OpenTask::handleResult(void* var1) {
    if (m_cb) {
        m_cb->onFileTaskFinished(m_file, var1);
    }
}
}

void FileSystemImpl$OpenTask::done() {
    if ((m_mode & 5) == 5) {
        m_file_system->closeAsync(m_file, nullptr);
    }
    m_file = nullptr;
    m_path.clear();
    m_cb = nullptr;
}
}

} // namespace fileSystem
} // namespace zombie
