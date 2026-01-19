package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoWheelieBin;

class IsoObject$6 extends IsoObjectFactory {
   IsoObject$6(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoWheelieBin(var1);
   }
}
