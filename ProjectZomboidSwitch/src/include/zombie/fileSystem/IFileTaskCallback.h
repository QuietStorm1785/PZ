#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace fileSystem {

class IFileTaskCallback {
public:
    virtual ~IFileTaskCallback() = default;
    void onFileTaskFinished(void* var1);
}
} // namespace fileSystem
} // namespace zombie
