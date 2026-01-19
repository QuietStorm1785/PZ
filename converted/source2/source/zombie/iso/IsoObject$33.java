package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoFire;

class IsoObject$33 extends IsoObjectFactory {
   IsoObject$33(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoFire(var1);
   }
}
