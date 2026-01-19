package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoCarBatteryCharger;

class IsoObject$22 extends IsoObjectFactory {
   IsoObject$22(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoCarBatteryCharger(var1);
   }
}
