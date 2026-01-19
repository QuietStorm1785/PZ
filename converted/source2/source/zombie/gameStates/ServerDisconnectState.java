package zombie.gameStates;

import zombie.GameWindow;
import zombie.IndieGL;
import zombie.Lua.LuaEventManager;
import zombie.Lua.LuaManager;
import zombie.characters.IsoPlayer;
import zombie.chat.ChatElement;
import zombie.core.Core;
import zombie.core.SpriteRenderer;
import zombie.gameStates.GameStateMachine.StateAction;
import zombie.input.GameKeyboard;
import zombie.iso.IsoCamera;
import zombie.iso.IsoWorld;
import zombie.iso.sprite.IsoSprite;
import zombie.ui.TextDrawObject;
import zombie.ui.TextManager;
import zombie.ui.TutorialManager;
import zombie.ui.UIFont;
import zombie.ui.UIManager;

public final class ServerDisconnectState extends GameState {
   private boolean keyDown = false;
   private int gridX = -1;
   private int gridY = -1;

   public void enter() {
      TutorialManager.instance.StealControl = false;
      UIManager.UI.clear();
      LuaEventManager.ResetCallbacks();
      LuaManager.call("ISServerDisconnectUI_OnServerDisconnectUI", GameWindow.kickReason);
   }

   public void exit() {
      GameWindow.kickReason = null;
   }

   public void render() {
      boolean var1 = true;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         if (IsoPlayer.players[var2] == null) {
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
         if (IsoPlayer.players[var5] != null) {
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
         String var6 = GameWindow.kickReason;
         if (var6 == null || var6.isEmpty()) {
            var6 = "Connection to server lost";
         }

         TextManager.instance
            .DrawStringCentre(UIFont.Medium, Core.getInstance().getScreenWidth() / 2, Core.getInstance().getScreenHeight() / 2, var6, 1.0, 1.0, 1.0, 1.0);
      }

      Core.getInstance().EndFrameUI();
   }

   public StateAction update() {
      if (!Core.bExiting && !GameKeyboard.isKeyDown(1)) {
         UIManager.update();
         return StateAction.Remain;
      } else {
         return StateAction.Continue;
      }
   }
}
