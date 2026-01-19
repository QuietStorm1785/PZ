package zombie.core;

import zombie.core.WinReqistry.StreamReader;

public class WinReqistry {
   public static String getSteamDirectory() {
      return readRegistry("HKEY_CURRENT_USER\\Software\\Valve\\Steam", "SteamPath");
   }

   public static final String readRegistry(String var0, String var1) {
      try {
         Process var2 = Runtime.getRuntime().exec("reg query \"" + var0 + "\" /v " + var1);
         StreamReader var3 = new StreamReader(var2.getInputStream());
         var3.start();
         var2.waitFor();
         var3.join();
         String var4 = var3.getResult();
         if (var4 != null && !var4.equals("")) {
            var4 = var4.substring(var4.indexOf("REG_SZ") + 7).trim();
            String[] var5 = var4.split("\t");
            return var5[var5.length - 1];
         } else {
            return null;
         }
      } catch (Exception var6) {
         return null;
      }
   }
}
