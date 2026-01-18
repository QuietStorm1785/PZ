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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class SpriteRendererStates {
public:
 SpriteRenderState m_populating = new SpriteRenderState(0);
 SpriteRenderState m_ready = nullptr;
 SpriteRenderState m_rendering = new SpriteRenderState(2);
 SpriteRenderState m_rendered = new SpriteRenderState(1);

 SpriteRenderState getPopulating() {
 return this->m_populating;
 }

 /**
 * Returns either the UI state, or populating state. Depends on the value of its stateUI.bActive
 */
 GenericSpriteRenderState getPopulatingActiveState() {
 return this->m_populating.getActiveState();
 }

 void setPopulating(SpriteRenderState populating) {
 this->m_populating = populating;
 }

 SpriteRenderState getReady() {
 return this->m_ready;
 }

 void setReady(SpriteRenderState ready) {
 this->m_ready = ready;
 }

 SpriteRenderState getRendering() {
 return this->m_rendering;
 }

 /**
 * Returns either the UI state, or rendering state. Depends on the value of its stateUI.bActive
 */
 GenericSpriteRenderState getRenderingActiveState() {
 return this->m_rendering.getActiveState();
 }

 void setRendering(SpriteRenderState rendering) {
 this->m_rendering = rendering;
 }

 SpriteRenderState getRendered() {
 return this->m_rendered;
 }

 void setRendered(SpriteRenderState rendered) {
 this->m_rendered = rendered;
 }

 void movePopulatingToReady() {
 this->m_ready = this->m_populating;
 this->m_populating = this->m_rendered;
 this->m_rendered = nullptr;
 this->m_ready.time = System.nanoTime();
 this->m_ready.onReady();
 }

 void moveReadyToRendering() {
 this->m_rendered = this->m_rendering;
 this->m_rendering = this->m_ready;
 this->m_ready = nullptr;
 this->m_rendering.onRenderAcquired();
 }
}
} // namespace sprite
} // namespace core
} // namespace zombie
