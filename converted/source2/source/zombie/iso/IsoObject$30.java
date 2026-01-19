package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoLightSwitch;

class IsoObject$30 extends IsoObjectFactory {
   IsoObject$30(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoLightSwitch(var1);
   }
}
