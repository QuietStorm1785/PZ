package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;

class IsoObject$5 extends IsoObjectFactory {
   IsoObject$5(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoPushableObject(var1);
   }
}
