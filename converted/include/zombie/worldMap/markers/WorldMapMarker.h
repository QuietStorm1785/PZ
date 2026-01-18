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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WorldMapMarker : public PooledObject {
public:
 void render(UIWorldMap var1);
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
