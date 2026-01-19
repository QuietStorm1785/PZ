package zombie.core;

import org.uncommons.maths.random.SecureRandomSeedGenerator;
import org.uncommons.maths.random.SeedException;
import org.uncommons.maths.random.SeedGenerator;

public final class Rand$PZSeedGenerator implements SeedGenerator {
   private static final SeedGenerator[] GENERATORS = new SeedGenerator[]{new SecureRandomSeedGenerator()};

   private Rand$PZSeedGenerator() {
   }

   public byte[] generateSeed(int var1) {
      for (SeedGenerator var5 : GENERATORS) {
         try {
            return var5.generateSeed(var1);
         } catch (SeedException var7) {
         }
      }

      throw new IllegalStateException("All available seed generation strategies failed.");
   }
}
