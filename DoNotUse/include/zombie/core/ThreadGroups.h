#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {

class ThreadGroups {
public:
    static const ThreadGroup Root = std::make_shared<ThreadGroup>("PZ");
    static const ThreadGroup Main = std::make_shared<ThreadGroup>(Root, "Main");
    static const ThreadGroup Workers = std::make_shared<ThreadGroup>(Root, "Workers");
    static const ThreadGroup Network = std::make_shared<ThreadGroup>(Root, "Network");
}
} // namespace core
} // namespace zombie
