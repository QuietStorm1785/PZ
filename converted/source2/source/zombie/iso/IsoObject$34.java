package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.vehicles.BaseVehicle;

class IsoObject$34 extends IsoObjectFactory {
   IsoObject$34(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new BaseVehicle(var1);
   }
}
