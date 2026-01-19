package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoBrokenGlass;

class IsoObject$21 extends IsoObjectFactory {
   IsoObject$21(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoBrokenGlass(var1);
   }
}
