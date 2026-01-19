package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoThumpable;

class IsoObject$19 extends IsoObjectFactory {
   IsoObject$19(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoThumpable(var1);
   }
}
