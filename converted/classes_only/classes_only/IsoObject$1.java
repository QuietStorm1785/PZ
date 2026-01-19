package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;

class IsoObject$1 extends IsoObjectFactory {
   IsoObject$1(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      IsoObject var2 = IsoObject.getNew();
      var2.sx = 0.0F;
      return var2;
   }
}
