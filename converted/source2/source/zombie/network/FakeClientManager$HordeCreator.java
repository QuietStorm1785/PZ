package zombie.network;

import zombie.core.utils.UpdateLimit;

class FakeClientManager$HordeCreator {
   private final int radius;
   private final int count;
   private final long interval;
   private final UpdateLimit hordeCreatorLimiter;

   public FakeClientManager$HordeCreator(int var1, int var2, long var3) {
      this.radius = var1;
      this.count = var2;
      this.interval = var3;
      this.hordeCreatorLimiter = new UpdateLimit(var3);
   }

   public String getCommand(int var1, int var2, int var3) {
      return String.format(
         "/createhorde2 -x %d -y %d -z %d -count %d -radius %d -crawler false -isFallOnFront false -isFakeDead false -knockedDown false -health 1 -outfit",
         var1,
         var2,
         var3,
         this.count,
         this.radius
      );
   }
}
