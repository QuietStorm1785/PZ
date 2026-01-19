package zombie.core.properties;

import java.util.Comparator;
import zombie.core.properties.PropertyContainer.MostTested;

class PropertyContainer$ProfileEntryComparitor implements Comparator<Object> {
   public PropertyContainer$ProfileEntryComparitor() {
   }

   @Override
   public int compare(Object var1, Object var2) {
      double var3 = ((MostTested)var1).count;
      double var5 = ((MostTested)var2).count;
      if (var3 > var5) {
         return -1;
      } else {
         return var5 > var3 ? 1 : 0;
      }
   }
}
