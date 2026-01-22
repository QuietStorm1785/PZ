#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace inventory {

class ItemPickerJava {
public:
    std::string name;
    int min;
    int max;
    std::vector<std::string> forceForItems;
    std::vector<std::string> forceForZones;
    std::vector<std::string> forceForTiles;
    std::vector<std::string> forceForRooms;
    int weightChance;
};

} // namespace inventory
} // namespace zombie
