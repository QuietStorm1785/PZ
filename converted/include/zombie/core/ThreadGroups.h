#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ThreadGroups {
public:
  static const ThreadGroup Root = new ThreadGroup("PZ");
  static const ThreadGroup Main = new ThreadGroup(Root, "Main");
  static const ThreadGroup Workers = new ThreadGroup(Root, "Workers");
  static const ThreadGroup Network = new ThreadGroup(Root, "Network");
}
} // namespace core
} // namespace zombie
