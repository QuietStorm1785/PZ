#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace sprite {

enum class RenderStateSlot {
   Populating(0),
   Ready(1),
   Rendering(2);

    const int m_index;

    private RenderStateSlot(int var3) {
      this.m_index = var3;
   }

    int index() {
      return this.m_index;
   }

    int count() {
    return 3;
   }
}
} // namespace sprite
} // namespace core
} // namespace zombie
