package zombie;

import zombie.Lua.LuaEventManager;

public class AmbientSoundManager$Ambient {
   public float x;
   public float y;
   public String name;
   public float radius;
   public float volume;
   long startTime;
   public int duration;
   public int worldSoundDelay;

   public AmbientSoundManager$Ambient(AmbientSoundManager var1, String var2, float var3, float var4, float var5, float var6) {
      this.this$0 = var1;
      this.worldSoundDelay = 0;
      this.name = var2;
      this.x = var3;
      this.y = var4;
      this.radius = var5;
      this.volume = var6;
      this.startTime = System.currentTimeMillis() / 1000L;
      this.duration = 2;
      this.update();
      LuaEventManager.triggerEvent("OnAmbientSound", var2, var3, var4);
   }

   public boolean finished() {
      long var1 = System.currentTimeMillis() / 1000L;
      return var1 - this.startTime >= this.duration;
   }

   public void update() {
      long var1 = System.currentTimeMillis() / 1000L;
      if (var1 - this.startTime >= this.worldSoundDelay) {
         WorldSoundManager.instance.addSound(null, (int)this.x, (int)this.y, 0, 600, 600);
      }
   }
}
