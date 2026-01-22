#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class RVSUtilityVehicle {
public:
    std::string zoneName;
    std::string scriptName;
    std::string outfits;
    int femaleChance;
    std::string vehicleDistrib;
   std::vector<std::string> items;
    int nbrOfItem;
    bool addTrailer;

   private RVSUtilityVehicle$Params() {
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
