package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.BSFurnace;

class IsoObject$26 extends IsoObjectFactory {
   IsoObject$26(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new BSFurnace(var1);
   }
}
