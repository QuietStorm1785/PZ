package zombie.popman;

import java.util.ArrayList;
import zombie.iso.IsoGridSquare;
import zombie.popman.PlayerSpawns.PlayerSpawn;

final class PlayerSpawns {
   private final ArrayList<PlayerSpawn> playerSpawns = new ArrayList<>();

   public void addSpawn(int var1, int var2, int var3) {
      PlayerSpawn var4 = new PlayerSpawn(var1, var2, var3);
      if (var4.building != null) {
         this.playerSpawns.add(var4);
      }
   }

   public void update() {
      long var1 = System.currentTimeMillis();

      for (int var3 = 0; var3 < this.playerSpawns.size(); var3++) {
         PlayerSpawn var4 = this.playerSpawns.get(var3);
         if (var4.counter == -1L) {
            var4.counter = var1;
         }

         if (var4.counter + 10000L <= var1) {
            this.playerSpawns.remove(var3--);
         }
      }
   }

   public boolean allowZombie(IsoGridSquare var1) {
      for (int var2 = 0; var2 < this.playerSpawns.size(); var2++) {
         PlayerSpawn var3 = this.playerSpawns.get(var2);
         if (!var3.allowZombie(var1)) {
            return false;
         }
      }

      return true;
   }
}
