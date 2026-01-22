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
namespace population {

class IClothingItemListener {
public:
    virtual ~IClothingItemListener() = default;
    void clothingItemChanged(const std::string& var1);
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
