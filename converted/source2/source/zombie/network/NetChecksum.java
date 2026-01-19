package zombie.network;

import zombie.core.Core;
import zombie.debug.DebugLog;
import zombie.network.NetChecksum.Checksummer;
import zombie.network.NetChecksum.Comparer;

public final class NetChecksum {
   public static final Checksummer checksummer = new Checksummer();
   public static final Comparer comparer = new Comparer();

   private static void noise(String var0) {
      if (!Core.bDebug) {
      }

      DebugLog.log("NetChecksum: " + var0);
   }
}
