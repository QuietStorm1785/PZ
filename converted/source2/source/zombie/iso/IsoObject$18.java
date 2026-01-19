package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoDoor;

class IsoObject$18 extends IsoObjectFactory {
   IsoObject$18(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoDoor(var1);
   }
}
