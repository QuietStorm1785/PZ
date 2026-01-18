#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IDrawable {
public:
 virtual ~IDrawable() = default;
 void Draw();
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
