#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/PooledObject.h"
#include "zombie/worldMap/UIWorldMap.h"

namespace zombie {
namespace worldMap {
namespace markers {


class WorldMapMarker : public PooledObject {
public:
   abstract void render(UIWorldMap var1);
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
