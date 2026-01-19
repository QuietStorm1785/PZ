package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoCombinationWasherDryer;

class IsoObject$35 extends IsoObjectFactory {
   IsoObject$35(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoCombinationWasherDryer(var1);
   }
}
