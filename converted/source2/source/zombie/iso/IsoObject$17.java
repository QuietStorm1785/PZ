package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoStove;

class IsoObject$17 extends IsoObjectFactory {
   IsoObject$17(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoStove(var1);
   }
}
