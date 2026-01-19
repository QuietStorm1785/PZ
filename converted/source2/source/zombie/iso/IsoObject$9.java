package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoCurtain;

class IsoObject$9 extends IsoObjectFactory {
   IsoObject$9(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoCurtain(var1);
   }
}
