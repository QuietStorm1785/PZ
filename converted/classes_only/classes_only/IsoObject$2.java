package zombie.iso;

import zombie.characters.IsoPlayer;
import zombie.iso.IsoObject.IsoObjectFactory;

class IsoObject$2 extends IsoObjectFactory {
   IsoObject$2(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoPlayer(var1);
   }
}
