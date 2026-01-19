package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoCompost;

class IsoObject$24 extends IsoObjectFactory {
   IsoObject$24(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoCompost(var1);
   }
}
