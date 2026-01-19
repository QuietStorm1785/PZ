package zombie.iso;

import zombie.iso.IsoObject.IsoObjectFactory;
import zombie.iso.objects.IsoMolotovCocktail;

class IsoObject$32 extends IsoObjectFactory {
   IsoObject$32(byte var1, String var2) {
      super(var1, var2);
   }

   protected IsoObject InstantiateObject(IsoCell var1) {
      return new IsoMolotovCocktail(var1);
   }
}
