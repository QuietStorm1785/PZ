package zombie.core.math;

import zombie.util.list.PZArrayUtil;

final class PZMath$UnitTests {
   private static final Runnable[] s_unitTests = new Runnable[0];

   private PZMath$UnitTests() {
   }

   private static void runAll() {
      PZArrayUtil.forEach(s_unitTests, Runnable::run);
   }
}
