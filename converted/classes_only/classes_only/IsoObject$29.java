package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoTree;

class IsoObject$29 extends IsoObjectFactory {
   IsoObject$29(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return IsoTree.getNew();
   }
}
