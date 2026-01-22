#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoMetaGrid {
public:
    int x;
    int y;
    int z;
    std::string enumValue;
    bool entireBuilding;
}
} // namespace iso
} // namespace zombie
