#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace sprite {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

enum class RenderStateSlot {
 Populating(0), Ready(1), Rendering(2);

 const int m_index;

 private RenderStateSlot(int int1){this->m_index = int1;}

int index() { return this->m_index; }

int count() { return 3; }
} // namespace sprite
} // namespace core
} // namespace zombie
} // namespace zombie
