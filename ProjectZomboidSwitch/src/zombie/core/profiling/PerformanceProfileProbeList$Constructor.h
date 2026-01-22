#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace profiling {

class PerformanceProfileProbeList {
public:
    virtual ~PerformanceProfileProbeList() = default;
    Probe get(const std::string& var1);
}
} // namespace profiling
} // namespace core
} // namespace zombie
