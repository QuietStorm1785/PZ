package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoJukebox;

class IsoObject$8 extends IsoObjectFactory {
   IsoObject$8(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoJukebox(var1);
   }
}
