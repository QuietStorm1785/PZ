package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoWorldInventoryObject;

class IsoObject$7 extends IsoObjectFactory {
   IsoObject$7(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoWorldInventoryObject(var1);
   }
}
