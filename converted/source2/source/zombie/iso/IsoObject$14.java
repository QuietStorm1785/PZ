package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoClothingDryer;

class IsoObject$14 extends IsoObjectFactory {
   IsoObject$14(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoClothingDryer(var1);
   }
}
