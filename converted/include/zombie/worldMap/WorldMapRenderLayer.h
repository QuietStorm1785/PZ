#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/popman/ObjectPool.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer.h"

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WorldMapRenderLayer {
public:
 WorldMapStyleLayer m_styleLayer;
 ArrayList<WorldMapFeature> m_features = std::make_unique<ArrayList<>>();
 static ObjectPool<WorldMapRenderLayer> s_pool = new ObjectPool<>(WorldMapRenderLayer::new);
}
} // namespace worldMap
} // namespace zombie
