package zombie.popman;

import zombie.WorldSoundManager.WorldSound;

class MPDebugInfo$MPSoundDebugInfo {
   int x;
   int y;
   int radius;
   boolean bRepeating;
   boolean sourceIsZombie;

   MPDebugInfo$MPSoundDebugInfo(WorldSound var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.radius = var1.radius;
      this.bRepeating = var1.bRepeating;
      this.sourceIsZombie = var1.sourceIsZombie;
   }
}
