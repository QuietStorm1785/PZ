#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class SpawnRegions {
public:
    int worldX;
    int worldY;
    int posX;
    int posY;
    int posZ;
}
} // namespace network
} // namespace zombie
