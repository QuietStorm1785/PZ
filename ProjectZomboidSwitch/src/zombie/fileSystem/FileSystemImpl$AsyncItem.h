#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace fileSystem {


class AsyncItem {
public:
    int m_id = 0;
    std::shared_ptr<FileTask> m_task;
    std::shared_ptr<void> m_future; // Replace with actual future type if available

    AsyncItem() = default;
};
} // namespace fileSystem
} // namespace zombie
