package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoZombieGiblets;

class IsoObject$31 extends IsoObjectFactory {
   IsoObject$31(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoZombieGiblets(var1);
   }
}
