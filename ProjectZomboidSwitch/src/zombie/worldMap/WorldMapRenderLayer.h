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
   const std::vector<WorldMapFeature> m_features = std::make_unique<std::vector<>>();
   static ObjectPool<WorldMapRenderLayer> s_pool = std::make_shared<ObjectPool>(WorldMapRenderLayer::new);
}
} // namespace worldMap
} // namespace zombie
