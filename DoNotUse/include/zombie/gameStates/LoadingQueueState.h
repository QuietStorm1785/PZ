#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/input/Keyboard.h"
#include "zombie/GameWindow.h"
#include "zombie/SoundManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/network/GameClient.h"
#include "zombie/ui/LoadingQueueUI.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace gameStates {


class LoadingQueueState : public GameState {
public:
    static bool bCancel = false;
    static bool bDone = false;
    static int placeInQueue = -1;
    bool bAButtonDown = false;
    static const LoadingQueueUI ui = std::make_shared<LoadingQueueUI>();

    void enter() {
      bCancel = false;
      bDone = false;
      placeInQueue = -1;
      this.bAButtonDown = GameWindow.ActivatedJoyPad != nullptr && GameWindow.ActivatedJoyPad.isAPressed();
      SoundManager.instance.setMusicState("Loading");
      if (GameClient.bClient) {
         GameClient.instance.sendLoginQueueRequest2();
      }
   }

    GameState redirectState() {
      return (GameState)(bCancel ? std::make_unique<MainScreenState>() : std::make_unique<GameLoadingState>());
   }

    void render() {
      Core.getInstance().StartFrame();
      Core.getInstance().EndFrame();
    bool var1 = UIManager.useUIFBO;
      UIManager.useUIFBO = false;
      Core.getInstance().StartFrameUI();
      SpriteRenderer.instance.renderi(nullptr, 0, 0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
      if (placeInQueue >= 0) {
         MainScreenState.instance.renderBackground();
         UIManager.render();
         ActiveMods.renderUI();
         ui.render();
      }

      Core.getInstance().EndFrameUI();
      UIManager.useUIFBO = var1;
   }

    StateAction update() {
      if (!GameClient.bClient) {
         return StateAction.Continue;
      } else {
    bool var1 = GameWindow.ActivatedJoyPad != nullptr && GameWindow.ActivatedJoyPad.isAPressed();
         if (var1) {
            if (this.bAButtonDown) {
               var1 = false;
            }
         } else {
            this.bAButtonDown = false;
         }

         if (var1 || Keyboard.isKeyDown(1) || !GameClient.instance.bConnected) {
            bCancel = true;
            SoundManager.instance.setMusicState("MainMenu");
            if (GameClient.connection != nullptr) {
               GameClient.instance.bConnected = false;
               GameClient.bClient = false;
               GameClient.connection.forceDisconnect("loading-queue-canceled");
               GameClient.connection = nullptr;
            }

            return StateAction.Continue;
         } else {
            return bDone ? StateAction.Continue : StateAction.Remain;
         }
      }
   }

    static void onConnectionImmediate() {
      bDone = true;
   }

    static void onPlaceInQueue(int var0) {
      placeInQueue = var0;
      ui.setPlaceInQueue(var0);
   }
}
} // namespace gameStates
} // namespace zombie
