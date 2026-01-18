#pragma once
#include "zombie/util/PooledObject.h"
#include "zombie/worldMap/UIWorldMap.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
namespace markers {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapMarker : public PooledObject {
public:
  abstract void render(UIWorldMap var1);
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
