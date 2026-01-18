#pragma once
#include "org/lwjglx/input/Keyboard.h"
#include "zombie/GameWindow.h"
#include "zombie/SoundManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/network/GameClient.h"
#include "zombie/ui/LoadingQueueUI.h"
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

class LoadingQueueState : public GameState {
public:
 static bool bCancel = false;
 static bool bDone = false;
 static int placeInQueue = -1;
 bool bAButtonDown = false;
 static const LoadingQueueUI ui = new LoadingQueueUI();

 void enter() {
 bCancel = false;
 bDone = false;
 placeInQueue = -1;
 this->bAButtonDown = GameWindow.ActivatedJoyPad != nullptr &&
 GameWindow.ActivatedJoyPad.isAPressed();
 SoundManager.instance.setMusicState("Loading");
 if (GameClient.bClient) {
 GameClient.instance.sendLoginQueueRequest2();
 }
 }

 GameState redirectState() {
 return (GameState)(bCancel ? std::make_unique<MainScreenState>()
 : std::make_unique<GameLoadingState>());
 }

 void render() {
 Core.getInstance().StartFrame();
 Core.getInstance().EndFrame();
 bool boolean0 = UIManager.useUIFBO;
 UIManager.useUIFBO = false;
 Core.getInstance().StartFrameUI();
 SpriteRenderer.instance.renderi(
 nullptr, 0, 0, Core.getInstance().getScreenWidth(),
 Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
 if (placeInQueue >= 0) {
 MainScreenState.instance.renderBackground();
 UIManager.render();
 ActiveMods.renderUI();
 ui.render();
 }

 Core.getInstance().EndFrameUI();
 UIManager.useUIFBO = boolean0;
 }

public
 GameStateMachine.StateAction update() {
 if (!GameClient.bClient) {
 return GameStateMachine.StateAction.Continue;
 } else {
 bool boolean0 = GameWindow.ActivatedJoyPad != nullptr &&
 GameWindow.ActivatedJoyPad.isAPressed();
 if (boolean0) {
 if (this->bAButtonDown) {
 boolean0 = false;
 }
 } else {
 this->bAButtonDown = false;
 }

 if (boolean0 || Keyboard.isKeyDown(1) ||
 !GameClient.instance.bConnected) {
 bCancel = true;
 SoundManager.instance.setMusicState("MainMenu");
 if (GameClient.connection != nullptr) {
 GameClient.instance.bConnected = false;
 GameClient.bClient = false;
 GameClient.connection.forceDisconnect("loading-queue-canceled");
 GameClient.connection = nullptr;
 }

 return GameStateMachine.StateAction.Continue;
 } else {
 return bDone ? GameStateMachine.StateAction.Continue
 : GameStateMachine.StateAction.Remain;
 }
 }
 }

 static void onConnectionImmediate() { bDone = true; }

 static void onPlaceInQueue(int place) {
 placeInQueue = place;
 ui.setPlaceInQueue(place);
 }
}
} // namespace gameStates
} // namespace zombie
