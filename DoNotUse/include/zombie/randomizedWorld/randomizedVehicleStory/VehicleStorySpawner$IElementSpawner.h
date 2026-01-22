#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawner/Element.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class VehicleStorySpawner {
public:
    virtual ~VehicleStorySpawner() = default;
    void spawn(VehicleStorySpawner var1, Element var2);
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
