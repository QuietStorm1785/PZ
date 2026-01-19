package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoTelevision;

class IsoObject$11 extends IsoObjectFactory {
   IsoObject$11(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoTelevision(var1);
   }
}
