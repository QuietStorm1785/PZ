package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoBarricade;

class IsoObject$28 extends IsoObjectFactory {
   IsoObject$28(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoBarricade(var1);
   }
}
