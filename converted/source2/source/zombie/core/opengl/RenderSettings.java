package zombie.core.opengl;

import zombie.characters.IsoPlayer;
import zombie.core.Color;
import zombie.core.Core;
import zombie.core.opengl.RenderSettings.PlayerRenderSettings;
import zombie.core.textures.Texture;
import zombie.debug.DebugLog;
import zombie.network.GameServer;

public final class RenderSettings {
   private static RenderSettings instance;
   private static Texture texture;
   private static final float AMBIENT_MIN_SHADER = 0.4F;
   private static final float AMBIENT_MAX_SHADER = 1.0F;
   private static final float AMBIENT_MIN_LEGACY = 0.4F;
   private static final float AMBIENT_MAX_LEGACY = 1.0F;
   private final PlayerRenderSettings[] playerSettings = new PlayerRenderSettings[4];
   private Color defaultClear = new Color(0, 0, 0, 1);

   public static RenderSettings getInstance() {
      if (instance == null) {
         instance = new RenderSettings();
      }

      return instance;
   }

   public RenderSettings() {
      for (int var1 = 0; var1 < this.playerSettings.length; var1++) {
         this.playerSettings[var1] = new PlayerRenderSettings();
      }

      texture = Texture.getSharedTexture("media/textures/weather/fogwhite.png");
      if (texture == null) {
         DebugLog.log("Missing texture: media/textures/weather/fogwhite.png");
      }
   }

   public PlayerRenderSettings getPlayerSettings(int var1) {
      return this.playerSettings[var1];
   }

   public void update() {
      if (!GameServer.bServer) {
         for (int var1 = 0; var1 < 4; var1++) {
            if (IsoPlayer.players[var1] != null) {
               this.playerSettings[var1].updateRenderSettings(var1, IsoPlayer.players[var1]);
            }
         }
      }
   }

   public void applyRenderSettings(int var1) {
      if (!GameServer.bServer) {
         this.getPlayerSettings(var1).applyRenderSettings(var1);
      }
   }

   public void legacyPostRender(int var1) {
      if (!GameServer.bServer) {
         if (Core.getInstance().RenderShader == null || Core.getInstance().getOffscreenBuffer() == null) {
            this.getPlayerSettings(var1).legacyPostRender(var1);
         }
      }
   }

   public float getAmbientForPlayer(int var1) {
      PlayerRenderSettings var2 = this.getPlayerSettings(var1);
      return var2 != null ? var2.getAmbient() : 0.0F;
   }

   public Color getMaskClearColorForPlayer(int var1) {
      PlayerRenderSettings var2 = this.getPlayerSettings(var1);
      return var2 != null ? var2.getMaskClearColor() : this.defaultClear;
   }
}
