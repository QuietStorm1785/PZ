#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Styles/TransparentStyle.h"
#include "zombie/core/opengl/GLState.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/PlayerCamera.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace sprite {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SpriteRenderState : public GenericSpriteRenderState {
public:
 TextureFBO fbo = nullptr;
 long time;
 const SpriteRenderStateUI stateUI;
 int playerIndex;
public
 PlayerCamera[] playerCamera = new PlayerCamera[4];
public
 float[] playerAmbient = new float[4];
 float maxZoomLevel = 0.0F;
 float minZoomLevel = 0.0F;
public
 float[] zoomLevel = new float[4];

public
 SpriteRenderState(int index) {
 super(index);

 for (int int0 = 0; int0 < 4; int0++) {
 this->playerCamera[int0] = new PlayerCamera(int0);
 }

 this->stateUI = new SpriteRenderStateUI(index);
 }

 void onRendered() {
 super.onRendered();
 this->stateUI.onRendered();
 }

 void onReady() {
 super.onReady();
 this->stateUI.onReady();
 }

 void CheckSpriteSlots() {
 if (this->stateUI.bActive) {
 this->stateUI.CheckSpriteSlots();
 } else {
 super.CheckSpriteSlots();
 }
 }

 void clear() {
 this->stateUI.clear();
 super.clear();
 }

 /**
 * Returns either the UI state, or this state. Depends on the value of
 * stateUI.bActive
 */
 GenericSpriteRenderState getActiveState() {
 return (GenericSpriteRenderState)(this->stateUI.bActive ? this->stateUI
 : this);
 }

 void prePopulating() {
 this->clear();
 this->fbo = Core.getInstance().getOffscreenBuffer();

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 this->playerCamera[int0].initFromIsoCamera(int0);
 this->playerAmbient[int0] =
 RenderSettings.getInstance().getAmbientForPlayer(int0);
 this->zoomLevel[int0] = Core.getInstance().getZoom(int0);
 this->maxZoomLevel = Core.getInstance().getMaxZoom();
 this->minZoomLevel = Core.getInstance().getMinZoom();
 }
 }

 this->defaultStyle = TransparentStyle.instance;
 this->bCursorVisible = Mouse.isCursorVisible();
 GLState.startFrame();
 }
}
} // namespace sprite
} // namespace core
} // namespace zombie
