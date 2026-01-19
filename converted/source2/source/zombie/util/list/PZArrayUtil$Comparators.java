package zombie.util.list;

import zombie.util.StringUtils;

public class PZArrayUtil$Comparators {
   public static <E> int referencesEqual(E var0, E var1) {
      return var0 == var1 ? 0 : 1;
   }

   public static <E> int objectsEqual(E var0, E var1) {
      return var0 != null && var0.equals(var1) ? 0 : 1;
   }

   public static int equalsIgnoreCase(String var0, String var1) {
      return StringUtils.equals(var0, var1) ? 0 : 1;
   }
}
