#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace sprite {

class SpriteRendererStates {
public:
    SpriteRenderState m_populating = std::make_shared<SpriteRenderState>(0);
    SpriteRenderState m_ready = nullptr;
    SpriteRenderState m_rendering = std::make_shared<SpriteRenderState>(2);
    SpriteRenderState m_rendered = std::make_shared<SpriteRenderState>(1);

    SpriteRenderState getPopulating() {
      return this.m_populating;
   }

    GenericSpriteRenderState getPopulatingActiveState() {
      return this.m_populating.getActiveState();
   }

    void setPopulating(SpriteRenderState var1) {
      this.m_populating = var1;
   }

    SpriteRenderState getReady() {
      return this.m_ready;
   }

    void setReady(SpriteRenderState var1) {
      this.m_ready = var1;
   }

    SpriteRenderState getRendering() {
      return this.m_rendering;
   }

    GenericSpriteRenderState getRenderingActiveState() {
      return this.m_rendering.getActiveState();
   }

    void setRendering(SpriteRenderState var1) {
      this.m_rendering = var1;
   }

    SpriteRenderState getRendered() {
      return this.m_rendered;
   }

    void setRendered(SpriteRenderState var1) {
      this.m_rendered = var1;
   }

    void movePopulatingToReady() {
      this.m_ready = this.m_populating;
      this.m_populating = this.m_rendered;
      this.m_rendered = nullptr;
      this.m_ready.time = System.nanoTime();
      this.m_ready.onReady();
   }

    void moveReadyToRendering() {
      this.m_rendered = this.m_rendering;
      this.m_rendering = this.m_ready;
      this.m_ready = nullptr;
      this.m_rendering.onRenderAcquired();
   }
}
} // namespace sprite
} // namespace core
} // namespace zombie
