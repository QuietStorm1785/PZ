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
    virtual void onFileTaskFinished(IFile file, void* result) = 0;
};
} // namespace fileSystem
} // namespace zombie
