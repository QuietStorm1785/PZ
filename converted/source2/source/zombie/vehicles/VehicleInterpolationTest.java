package zombie.vehicles;

import java.nio.ByteBuffer;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TestRule;
import zombie.vehicles.VehicleInterpolationTest.1;

public class VehicleInterpolationTest extends Assert {
   final VehicleInterpolation interpolation = new VehicleInterpolation();
   final float[] physics = new float[27];
   final float[] engineSound = new float[2];
   final ByteBuffer bb = ByteBuffer.allocateDirect(255);
   final int tick = 100;
   final int delay = 300;
   final int history = 200;
   final int bufferingIterations = 4;
   @Rule
   public TestRule watchman = new 1(this);

   @Before
   public void setup() {
      this.interpolation.clear();
      this.interpolation.delay = 300;
      this.interpolation.history = 500;
      this.interpolation.reset();
   }

   @Test
   public void normalTest() {
      long var1 = 9223372036853775807L;

      for (int var3 = 1; var3 < 30; var3++) {
         this.bb.position(0);
         this.interpolation.interpolationDataAdd(this.bb, var1, var3 * 2, var3 * 2, 0.0F, var1);
         boolean var4 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 298L);
         if (var3 < 4) {
            assertFalse(var4);
         } else {
            assertTrue(var4);
            assertEquals((var3 - 4 + 1) * 2.0F, this.physics[0], 0.2F);
         }

         boolean var5 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 298L + 50L);
         if (var3 < 4) {
            assertFalse(var4);
         } else {
            assertTrue(var4);
            assertEquals((var3 - 4 + 1) * 2.0F + 1.0F, this.physics[0], 0.2F);
         }

         var1 += 100L;
      }
   }

   @Test
   public void interpolationTest() {
      byte var1 = 0;

      for (int var2 = 1; var2 < 30; var2++) {
         this.bb.position(0);
         if (var2 % 2 == 1) {
            this.interpolation.interpolationDataAdd(this.bb, var1, var2, var2, 0.0F, var1);
         }

         boolean var3 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 298);
         if (var2 < 4) {
            assertFalse(var3);
         } else {
            assertTrue(var3);
            assertEquals(var2 - 4 + 1, this.physics[0], 0.2F);
         }

         var1 += 100;
      }
   }

   @Test
   public void interpolationMicroStepTest() {
      byte var1 = 0;

      for (int var2 = 1; var2 < 30; var2++) {
         this.bb.position(0);
         this.interpolation.interpolationDataAdd(this.bb, var1, var2, var2, 0.0F, var1);
         boolean var3 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 298);
         if (var2 < 4) {
            assertFalse(var3);
         } else {
            assertTrue(var3);
            assertEquals(var2 - 4 + 1, this.physics[0], 0.2F);
         }

         var1 += 100;
      }

      for (int var5 = 30; var5 < 35; var5++) {
         this.interpolation.interpolationDataAdd(this.bb, var1, var5, var5, 0.0F, var1);

         for (int var6 = 0; var6 < 100; var6++) {
            boolean var4 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 300 + 100 * var6 / 100);
            assertTrue(var4);
            assertEquals(var5 - 4 + 1 + var6 / 100.0F, this.physics[0], 0.001F);
         }

         var1 += 100;
      }
   }

   @Test
   public void interpolationMicroStepTest2() {
      long var1 = 0L;
      byte var3 = 50;

      for (int var4 = 1; var4 < 30; var4++) {
         this.bb.position(0);
         this.interpolation.interpolationDataAdd(this.bb, var1, var4, var4, 0.0F, var1);
         boolean var5 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 298L);
         System.out.println(var4 + "   " + var1 + " " + var5 + " " + this.physics[0]);
         var1 += var3;
      }

      for (int var7 = 30; var7 < 35; var7++) {
         this.interpolation.interpolationDataAdd(this.bb, var1, var7, var7, 0.0F, var1);

         for (int var8 = 0; var8 < 10; var8++) {
            boolean var6 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 300L + var3 * var8 / 10);
            System.out.println(var7 + "." + var8 + " " + (var1 + var3 * var8 / 10) + " " + var6 + " " + this.physics[0] + " " + (var7 - 6.0F + var8 / 10.0F));
            assertTrue(var6);
            assertEquals(var7 - 6.0F + var8 / 10.0F, this.physics[0], 0.001F);
         }

         var1 += var3;
      }
   }

   @Test
   public void testBufferRestoring() {
      int var1 = 0;

      for (int var2 = 1; var2 < 30; var2++) {
         this.bb.position(0);
         this.interpolation.interpolationDataAdd(this.bb, var1, var2, var2, 0.0F, var1);
         boolean var3 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 298);
         System.out.println(var2 + " " + var1 + " " + var3 + " " + this.physics[0]);
         if (var2 >= 4 && (var2 <= 10 || var2 >= 14)) {
            assertTrue(var3);
            assertEquals(var2 - 4 + 1, this.physics[0], 0.2F);
         }

         if (var2 == 10) {
            var1 += 500;
         }

         var1 += 100;
      }
   }

   @Test
   public void normalTestBufferRestoring2() {
      byte var1 = 0;

      for (int var2 = 1; var2 < 100; var2++) {
         this.bb.position(0);
         boolean var3 = var2 < 15 || var2 > 21;
         if (var3) {
            this.interpolation.interpolationDataAdd(this.bb, var1, var2, 0.0F, 0.0F, var1);
         }

         boolean var4 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 298);
         System.out.println(var2 + " " + var4 + " " + this.physics[0]);
         if (var2 >= 4 && (var2 <= 17 || var2 >= 25)) {
            assertTrue(var4);
            if (var2 >= 17 && var2 <= 21) {
               assertEquals(14.0F, this.physics[0], 0.1F);
            } else {
               assertEquals(var2 - 4 + 1, this.physics[0], 0.1F);
            }
         } else {
            assertFalse(var4);
         }

         var1 += 100;
      }
   }

   @Test
   public void normalTestBufferRestoring3() {
      byte var1 = 0;

      for (int var2 = 1; var2 < 40; var2++) {
         this.bb.position(0);
         if (var2 != 10 && var2 != 12 && var2 != 13 && var2 != 15 && var2 != 16) {
            this.interpolation.interpolationDataAdd(this.bb, var1, var2, 0.0F, 0.0F, var1);
         }

         if (var2 > 26 && var2 < 33) {
            this.interpolation.interpolationDataAdd(this.bb, var1 + 50, var2 + 0.5F, 0.0F, 0.0F, var1);
         }

         boolean var3 = this.interpolation.interpolationDataGet(this.physics, this.engineSound, var1 - 298);
         System.out.println(var2 + " " + var3 + " " + this.physics[0]);
         if (var2 < 4) {
            assertFalse(var3);
         } else {
            assertTrue(var3);
            assertEquals(var2 - 4 + 1, this.physics[0], 0.1F);
         }

         var1 += 100;
      }
   }
}
