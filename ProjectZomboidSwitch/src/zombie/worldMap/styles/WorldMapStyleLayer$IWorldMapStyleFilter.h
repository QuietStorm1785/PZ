#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/WorldMapFeature.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/FilterArgs.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleLayer {
public:
    virtual ~WorldMapStyleLayer() = default;
    bool filter(WorldMapFeature var1, FilterArgs var2);
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
