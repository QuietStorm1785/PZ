package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoDeadBody;

class IsoObject$12 extends IsoObjectFactory {
   IsoObject$12(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoDeadBody(var1);
   }
}
