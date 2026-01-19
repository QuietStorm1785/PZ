package zombie;

import fmod.fmod.FMODSoundEmitter;
import zombie.Lua.LuaEventManager;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.core.Core;
import zombie.input.Mouse;
import zombie.iso.IsoCamera;
import zombie.iso.IsoUtils;
import zombie.network.GameClient;

public final class AmbientStreamManager$Ambient {
   public float x;
   public float y;
   public String name;
   float radius;
   float volume;
   int worldSoundRadius;
   int worldSoundVolume;
   public boolean trackMouse = false;
   final FMODSoundEmitter emitter = new FMODSoundEmitter();

   public AmbientStreamManager$Ambient(String var1, float var2, float var3, float var4, float var5) {
      this(var1, var2, var3, var4, var5, false);
   }

   public AmbientStreamManager$Ambient(String var1, float var2, float var3, float var4, float var5, boolean var6) {
      this.name = var1;
      this.x = var2;
      this.y = var3;
      this.radius = var4;
      this.volume = var5;
      this.emitter.x = var2;
      this.emitter.y = var3;
      this.emitter.z = 0.0F;
      this.emitter.playAmbientSound(var1);
      this.update();
      LuaEventManager.triggerEvent("OnAmbientSound", var1, var2, var3);
   }

   public boolean finished() {
      return this.emitter.isEmpty();
   }

   public void update() {
      this.emitter.tick();
      if (this.trackMouse && IsoPlayer.getInstance() != null) {
         float var1 = Mouse.getXA();
         float var2 = Mouse.getYA();
         var1 -= IsoCamera.getScreenLeft(IsoPlayer.getPlayerIndex());
         var2 -= IsoCamera.getScreenTop(IsoPlayer.getPlayerIndex());
         var1 *= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
         var2 *= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
         int var3 = (int)IsoPlayer.getInstance().getZ();
         this.emitter.x = (int)IsoUtils.XToIso(var1, var2, var3);
         this.emitter.y = (int)IsoUtils.YToIso(var1, var2, var3);
      }

      if (!GameClient.bClient && this.worldSoundRadius > 0 && this.worldSoundVolume > 0) {
         WorldSoundManager.instance.addSound(null, (int)this.x, (int)this.y, 0, this.worldSoundRadius, this.worldSoundVolume);
      }
   }

   public void repeatWorldSounds(int var1, int var2) {
      this.worldSoundRadius = var1;
      this.worldSoundVolume = var2;
   }

   private IsoGameCharacter getClosestListener(float var1, float var2) {
      IsoPlayer var3 = null;
      float var4 = Float.MAX_VALUE;

      for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
         IsoPlayer var6 = IsoPlayer.players[var5];
         if (var6 != null && var6.getCurrentSquare() != null) {
            float var7 = var6.getX();
            float var8 = var6.getY();
            float var9 = IsoUtils.DistanceToSquared(var7, var8, var1, var2);
            if (var6.Traits.HardOfHearing.isSet()) {
               var9 *= 4.5F;
            }

            if (var6.Traits.Deaf.isSet()) {
               var9 = Float.MAX_VALUE;
            }

            if (var9 < var4) {
               var3 = var6;
               var4 = var9;
            }
         }
      }

      return var3;
   }
}
