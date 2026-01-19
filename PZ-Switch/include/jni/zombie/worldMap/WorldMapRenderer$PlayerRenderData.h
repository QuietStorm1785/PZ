#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/ModelSlotRenderData.h"

namespace zombie {
namespace worldMap {


class WorldMapRenderer {
:
    ModelSlotRenderData m_modelSlotRenderData;
    float m_angle;
    float m_x;
    float m_y;

   private WorldMapRenderer$PlayerRenderData() {
   }
}
} // namespace worldMap
} // namespace zombie
