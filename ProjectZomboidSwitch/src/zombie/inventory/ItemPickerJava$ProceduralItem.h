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
   public List<std::string> forceForItems;
   public List<std::string> forceForZones;
   public List<std::string> forceForTiles;
   public List<std::string> forceForRooms;
    int weightChance;
}
} // namespace inventory
} // namespace zombie
