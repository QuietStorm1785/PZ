package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoMannequin;

class IsoObject$25 extends IsoObjectFactory {
   IsoObject$25(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoMannequin(var1);
   }
}
