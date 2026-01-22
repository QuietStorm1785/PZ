#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/WorldMapRenderer.h"
#include "zombie/worldMap/WorldMapRenderer/Drawer.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleLayer {
public:
    WorldMapRenderer renderer;
    Drawer drawer;
    int cellX;
    int cellY;
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
