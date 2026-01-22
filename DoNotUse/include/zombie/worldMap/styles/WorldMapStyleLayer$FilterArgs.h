#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/WorldMapRenderer.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleLayer {
public:
    WorldMapRenderer renderer;
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
