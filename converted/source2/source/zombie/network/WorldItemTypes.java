package zombie.network;

import java.nio.ByteBuffer;
import zombie.iso.IsoObject;

public class WorldItemTypes {
   public static IsoObject createFromBuffer(ByteBuffer var0) {
      Object var1 = null;
      return IsoObject.factoryFromFileInput(null, var0);
   }
}
