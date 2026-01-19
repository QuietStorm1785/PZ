package zombie.util;

import gnu.trove.set.hash.THashSet;
import java.util.ArrayList;
import java.util.List;

final class Pool$PoolStacks {
   final THashSet<IPooledObject> inUse = new THashSet();
   final List<IPooledObject> released = new ArrayList<>();

   Pool$PoolStacks() {
      this.inUse.setAutoCompactionFactor(0.0F);
   }
}
