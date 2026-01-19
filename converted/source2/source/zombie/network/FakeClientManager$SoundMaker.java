package zombie.network;

import zombie.core.utils.UpdateLimit;

class FakeClientManager$SoundMaker {
   private final int radius;
   private final int interval;
   private final String message;
   private final UpdateLimit soundMakerLimiter;

   public FakeClientManager$SoundMaker(int var1, int var2, String var3) {
      this.radius = var2;
      this.message = var3;
      this.interval = var1;
      this.soundMakerLimiter = new UpdateLimit(var1);
   }
}
