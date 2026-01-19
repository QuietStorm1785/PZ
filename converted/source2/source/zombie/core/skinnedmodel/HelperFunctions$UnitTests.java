package zombie.core.skinnedmodel;

import zombie.util.list.PZArrayUtil;

final class HelperFunctions$UnitTests {
   private static final Runnable[] s_unitTests = new Runnable[0];

   private HelperFunctions$UnitTests() {
   }

   private static void runAll() {
      PZArrayUtil.forEach(s_unitTests, Runnable::run);
   }
}
