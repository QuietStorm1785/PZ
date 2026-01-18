#pragma once
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/TutorialManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ServerDisconnectState : public GameState {
public:
 bool keyDown = false;
 int gridX = -1;
 int gridY = -1;

 void enter() {
 TutorialManager.instance.StealControl = false;
 UIManager.UI.clear();
 LuaEventManager.ResetCallbacks();
 LuaManager.call("ISServerDisconnectUI_OnServerDisconnectUI",
 GameWindow.kickReason);
 }

 void exit() { GameWindow.kickReason = nullptr; }

 void render() {
 bool boolean0 = true;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 if (IsoPlayer.players[int0] == nullptr) {
 if (int0 == 0) {
 SpriteRenderer.instance.prePopulating();
 }
 } else {
 IsoPlayer.setInstance(IsoPlayer.players[int0]);
 IsoCamera.CamCharacter = IsoPlayer.players[int0];
 Core.getInstance().StartFrame(int0, boolean0);
 IsoCamera.frameState.set(int0);
 boolean0 = false;
 IsoSprite.globalOffsetX = -1.0F;
 IsoWorld.instance.render();
 Core.getInstance().EndFrame(int0);
 }
 }

 Core.getInstance().RenderOffScreenBuffer();

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 if (IsoPlayer.players[int1] != nullptr) {
 Core.getInstance().StartFrameText(int1);
 IndieGL.disableAlphaTest();
 IndieGL.glDisable(2929);
 TextDrawObject.RenderBatch(int1);
 ChatElement.RenderBatch(int1);

 try {
 Core.getInstance().EndFrameText(int1);
 } catch (Exception exception) {
 }
 }
 }

 if (Core.getInstance().StartFrameUI()) {
 UIManager.render();
 std::string string = GameWindow.kickReason;
 if (string.empty() || string.empty()) {
 string = "Connection to server lost";
 }

 TextManager.instance.DrawStringCentre(
 UIFont.Medium, Core.getInstance().getScreenWidth() / 2,
 Core.getInstance().getScreenHeight() / 2, string, 1.0, 1.0, 1.0, 1.0);
 }

 Core.getInstance().EndFrameUI();
 }

public
 GameStateMachine.StateAction update() {
 if (!Core.bExiting && !GameKeyboard.isKeyDown(1) {
 UIManager.update();
 return GameStateMachine.StateAction.Remain;
 } else {
 return GameStateMachine.StateAction.Continue;
 }
 }
}
} // namespace gameStates
} // namespace zombie
