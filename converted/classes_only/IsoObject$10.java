package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoRadio;

class IsoObject$10 extends IsoObjectFactory {
   IsoObject$10(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoRadio(var1);
   }
}
