#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace fileSystem {

class IFileTask2Callback {
public:
    virtual ~IFileTask2Callback() = default;
    void onFileTaskFinished(IFile var1, void* var2);
}
} // namespace fileSystem
} // namespace zombie
