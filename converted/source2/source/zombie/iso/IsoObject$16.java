package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoFireplace;

class IsoObject$16 extends IsoObjectFactory {
   IsoObject$16(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoFireplace(var1);
   }
}
