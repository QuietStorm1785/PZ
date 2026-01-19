package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoGenerator;

class IsoObject$23 extends IsoObjectFactory {
   IsoObject$23(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoGenerator(var1);
   }
}
