package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoClothingWasher;

class IsoObject$15 extends IsoObjectFactory {
   IsoObject$15(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoClothingWasher(var1);
   }
}
