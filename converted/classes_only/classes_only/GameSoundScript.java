package zombie.scripting.objects;

import zombie.audio.GameSound;
import zombie.audio.GameSoundClip;
import zombie.audio.GameSound.MasterVolume;
import zombie.core.math.PZMath;
import zombie.scripting.ScriptParser;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.Value;

public final class GameSoundScript extends BaseScriptObject {
   public final GameSound gameSound = new GameSound();

   public void Load(String var1, String var2) {
      this.gameSound.name = var1;
      Block var3 = ScriptParser.parse(var2);
      var3 = (Block)var3.children.get(0);

      for (Value var5 : var3.values) {
         String[] var6 = var5.string.split("=");
         String var7 = var6[0].trim();
         String var8 = var6[1].trim();
         if ("category".equals(var7)) {
            this.gameSound.category = var8;
         } else if ("is3D".equals(var7)) {
            this.gameSound.is3D = Boolean.parseBoolean(var8);
         } else if ("loop".equals(var7)) {
            this.gameSound.loop = Boolean.parseBoolean(var8);
         } else if ("master".equals(var7)) {
            this.gameSound.master = MasterVolume.valueOf(var8);
         } else if ("maxInstancesPerEmitter".equals(var7)) {
            this.gameSound.maxInstancesPerEmitter = PZMath.tryParseInt(var8, -1);
         }
      }

      for (Block var11 : var3.children) {
         if ("clip".equals(var11.type)) {
            GameSoundClip var12 = this.LoadClip(var11);
            this.gameSound.clips.add(var12);
         }
      }
   }

   private GameSoundClip LoadClip(Block var1) {
      GameSoundClip var2 = new GameSoundClip(this.gameSound);

      for (Value var4 : var1.values) {
         String[] var5 = var4.string.split("=");
         String var6 = var5[0].trim();
         String var7 = var5[1].trim();
         if ("distanceMax".equals(var6)) {
            var2.distanceMax = Integer.parseInt(var7);
            var2.initFlags = (short)(var2.initFlags | GameSoundClip.INIT_FLAG_DISTANCE_MAX);
         } else if ("distanceMin".equals(var6)) {
            var2.distanceMin = Integer.parseInt(var7);
            var2.initFlags = (short)(var2.initFlags | GameSoundClip.INIT_FLAG_DISTANCE_MIN);
         } else if ("event".equals(var6)) {
            var2.event = var7;
         } else if ("file".equals(var6)) {
            var2.file = var7;
         } else if ("pitch".equals(var6)) {
            var2.pitch = Float.parseFloat(var7);
         } else if ("volume".equals(var6)) {
            var2.volume = Float.parseFloat(var7);
         } else if ("reverbFactor".equals(var6)) {
            var2.reverbFactor = Float.parseFloat(var7);
         } else if ("reverbMaxRange".equals(var6)) {
            var2.reverbMaxRange = Float.parseFloat(var7);
         }
      }

      return var2;
   }

   public void reset() {
      this.gameSound.reset();
   }
}
