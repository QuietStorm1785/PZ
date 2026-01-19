#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class PredicatedFileWatcher {
:
    virtual ~PredicatedFileWatcher() = default;
    void call(std::string_view var1);
}
} // namespace zombie
