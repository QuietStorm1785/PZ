package zombie.ui;

import java.util.ArrayDeque;
import java.util.Collection;
import zombie.ui.RadarPanel.ZombiePos;

class RadarPanel$ZombiePosPool {
   private ArrayDeque<ZombiePos> pool = new ArrayDeque<>();

   private RadarPanel$ZombiePosPool() {
   }

   public ZombiePos alloc(float var1, float var2) {
      return this.pool.isEmpty() ? new ZombiePos(var1, var2) : this.pool.pop().set(var1, var2);
   }

   public void release(Collection<ZombiePos> var1) {
      this.pool.addAll(var1);
   }
}
