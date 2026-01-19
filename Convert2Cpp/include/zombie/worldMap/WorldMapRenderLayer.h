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


class WorldMapRenderLayer {
public:
    WorldMapStyleLayer m_styleLayer;
   final ArrayList<WorldMapFeature> m_features = std::make_unique<ArrayList<>>();
   static ObjectPool<WorldMapRenderLayer> s_pool = new ObjectPool(WorldMapRenderLayer::new);
}
} // namespace worldMap
} // namespace zombie
