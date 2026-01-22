#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelOutlines {
public:
    bool m_startFrame;
    int m_playerIndex;

    void render() {
      if (this.m_startFrame) {
         ModelOutlines.instance.startFrame(this.m_playerIndex);
      } else {
         ModelOutlines.instance.endFrame(this.m_playerIndex);
      }
   }

    void postRender() {
      ModelOutlines.instance.m_drawerPool.release(this);
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
