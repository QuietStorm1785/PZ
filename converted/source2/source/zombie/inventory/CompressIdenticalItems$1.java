package zombie.inventory;

import zombie.inventory.CompressIdenticalItems.PerThreadData;

class CompressIdenticalItems$1 extends ThreadLocal<PerThreadData> {
   protected PerThreadData initialValue() {
      return new PerThreadData();
   }
}
