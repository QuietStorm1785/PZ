#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IClothingItemListener {
public:
 virtual ~IClothingItemListener() = default;
 void clothingItemChanged(std::string_view itemGuid);
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
