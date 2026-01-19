package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoBarbecue;

class IsoObject$13 extends IsoObjectFactory {
   IsoObject$13(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoBarbecue(var1);
   }
}
