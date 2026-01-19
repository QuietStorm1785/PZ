package zombie.core.znet;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.debug.LogSeverity;

public class ZNet {
   private static final SimpleDateFormat s_logSdf = new SimpleDateFormat("dd-MM-yy HH:mm:ss.SSS");

   public static native void init();

   private static native void setLogLevel(int var0);

   public static void SetLogLevel(int var0) {
      DebugLog.enableLog(DebugType.Network, switch (var0) {
         case 0 -> LogSeverity.Warning;
         case 1 -> LogSeverity.General;
         case 2 -> LogSeverity.Debug;
         default -> LogSeverity.Error;
      });
   }

   public static void SetLogLevel(LogSeverity var0) {
      setLogLevel(var0.ordinal());
   }

   private static void logPutsCallback(String var0) {
      String var1 = s_logSdf.format(Calendar.getInstance().getTime());
      DebugLog.Network.print("[" + var1 + "] > " + var0);
      System.out.flush();
   }
}
