package zombie.inventory;

import java.nio.ByteBuffer;
import zombie.inventory.CompressIdenticalItems.PerCallData;

class CompressIdenticalItems$PerThreadData {
   PerCallData saveVars;
   ByteBuffer itemCompareBuffer = ByteBuffer.allocate(1024);

   private CompressIdenticalItems$PerThreadData() {
   }

   PerCallData allocSaveVars() {
      if (this.saveVars == null) {
         return new PerCallData();
      } else {
         PerCallData var1 = this.saveVars;
         var1.reset();
         this.saveVars = this.saveVars.next;
         return var1;
      }
   }
}
