#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class PredicatedFileWatcher {
:
    virtual ~PredicatedFileWatcher() = default;
    void call(T var1);
}
} // namespace zombie
