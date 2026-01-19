package zombie.iso;

import zombie.characters.IsoZombie;
import zombie.iso.IsoObject.IsoObjectFactory;

class IsoObject$4 extends IsoObjectFactory {
   IsoObject$4(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoZombie(var1);
   }
}
