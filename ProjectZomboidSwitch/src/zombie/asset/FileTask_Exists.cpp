#include <string>
#include "zombie/asset/FileTask_Exists.h"

namespace zombie {
namespace asset {

FileTask_Exists::FileTask_Exists(const std::string& var1, IFileTaskCallback var2, FileSystem var3)
    : FileTask(var3, var2), fileName(var1)
{
    // Constructor logic as per header
}
}

void FileTask_Exists::done() {
    // No-op by default
}
}

void* FileTask_Exists::call() {
    // Return true if file exists, false otherwise
    std::ifstream file(fileName);
    bool exists = file.good();
    return reinterpret_cast<void*>(exists);
}
}

} // namespace asset
} // namespace zombie
