package zombie.characters;

public enum IsoZombie$ZombieSound {
   Burned(10),
   DeadCloseKilled(10),
   DeadNotCloseKilled(10),
   Hurt(10),
   Idle(15),
   Lunge(40),
   MAX(-1);

   private int radius;
   private static final IsoZombie$ZombieSound[] values = values();

   private IsoZombie$ZombieSound(int var3) {
      this.radius = var3;
   }

   public int radius() {
      return this.radius;
   }

   public static IsoZombie$ZombieSound fromIndex(int var0) {
      return var0 >= 0 && var0 < values.length ? values[var0] : MAX;
   }
}
