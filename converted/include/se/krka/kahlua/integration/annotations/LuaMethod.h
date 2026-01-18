#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace annotations {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

public
@interface LuaMethod {
  std::string name();

  bool global();
}
} // namespace annotations
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
