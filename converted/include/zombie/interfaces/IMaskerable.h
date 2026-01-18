#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Mask.h"

namespace zombie {
namespace interfaces {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IMaskerable {
public:
 virtual ~IMaskerable() = default;
 Mask getMask();
}
} // namespace interfaces
} // namespace zombie
