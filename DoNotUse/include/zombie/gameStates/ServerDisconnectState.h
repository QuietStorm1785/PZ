#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/TutorialManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace gameStates {


class ServerDisconnectState : public GameState {
public:
    bool keyDown = false;
    int gridX = -1;
    int gridY = -1;

    void enter() {
      TutorialManager.instance.StealControl = false;
      UIManager.UI.clear();
      LuaEventManager.ResetCallbacks();
      LuaManager.call("ISServerDisconnectUI_OnServerDisconnectUI", GameWindow.kickReason);
   }

    void exit() {
      GameWindow.kickReason = nullptr;
   }

    void render() {
    bool var1 = true;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         if (IsoPlayer.players[var2] == nullptr) {
            if (var2 == 0) {
               SpriteRenderer.instance.prePopulating();
            }
         } else {
            IsoPlayer.setInstance(IsoPlayer.players[var2]);
            IsoCamera.CamCharacter = IsoPlayer.players[var2];
            Core.getInstance().StartFrame(var2, var1);
            IsoCamera.frameState.set(var2);
            var1 = false;
            IsoSprite.globalOffsetX = -1.0F;
            IsoWorld.instance.render();
            Core.getInstance().EndFrame(var2);
         }
      }

      Core.getInstance().RenderOffScreenBuffer();

      for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
         if (IsoPlayer.players[var5] != nullptr) {
            Core.getInstance().StartFrameText(var5);
            IndieGL.disableAlphaTest();
            IndieGL.glDisable(2929);
            TextDrawObject.RenderBatch(var5);
            ChatElement.RenderBatch(var5);

            try {
               Core.getInstance().EndFrameText(var5);
            } catch (Exception var4) {
            }
         }
      }

      if (Core.getInstance().StartFrameUI()) {
         UIManager.render();
    std::string var6 = GameWindow.kickReason;
         if (var6 == nullptr || var6.empty()) {
            var6 = "Connection to server lost";
         }

         TextManager.instance
            .DrawStringCentre(UIFont.Medium, Core.getInstance().getScreenWidth() / 2, Core.getInstance().getScreenHeight() / 2, var6, 1.0, 1.0, 1.0, 1.0);
      }

      Core.getInstance().EndFrameUI();
   }

    StateAction update() {
      if (!Core.bExiting && !GameKeyboard.isKeyDown(1)) {
         UIManager.update();
         return StateAction.Remain;
      } else {
         return StateAction.Continue;
      }
   }
}
} // namespace gameStates
} // namespace zombie
