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
namespace visual {

class IHumanVisual {
public:
    virtual ~IHumanVisual() = default;
    HumanVisual getHumanVisual();

    void getItemVisuals(ItemVisuals var1);

    bool isFemale();

    bool isZombie();

    bool isSkeleton();
}
} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
