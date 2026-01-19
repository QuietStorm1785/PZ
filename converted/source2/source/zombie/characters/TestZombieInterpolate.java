package zombie.characters;

import org.junit.Assert;
import org.junit.Test;
import zombie.characters.NetworkCharacter.Transform;
import zombie.iso.Vector2;

public class TestZombieInterpolate extends Assert {
   @Test
   public void test_predictor_stay() {
      NetworkCharacter var1 = new NetworkCharacter();
      short var2 = 10000;
      short var3 = 250;
      float var4 = 100.0F;
      float var5 = 200.0F;
      float var6 = 1.0F;
      float var7 = -1.0F;
      var1.predict(var3, var2, var4, var5, var6, var7);

      for (int var8 = 0; var8 < 10; var8++) {
         Transform var9 = var1.predict(var3, var2, var4, var5, var6, var7);
         assertEquals(100.0F, var9.position.x, 0.01F);
         assertEquals(200.0F, var9.position.y, 0.01F);
      }

      for (int var10 = 0; var10 < 10; var10++) {
         var2 += var3;
         Transform var11 = var1.predict(var3, var2, var4, var5, var6, var7);
         assertEquals(100.0F, var11.position.x, 0.01F);
         assertEquals(200.0F, var11.position.y, 0.01F);
      }
   }

   @Test
   public void test_predictor_normal_go() {
      NetworkCharacter var1 = new NetworkCharacter();
      short var2 = 10000;
      short var3 = 250;
      float var4 = 100.0F;
      float var5 = 200.0F;
      float var6 = 1.0F;
      float var7 = -1.0F;
      Transform var8 = var1.predict(var3, var2, var4, var5, var6, var7);
      assertEquals(100.0F, var8.position.x, 0.01F);
      assertEquals(200.0F, var8.position.y, 0.01F);

      for (int var9 = 0; var9 < 30; var9++) {
         var2 += var3;
         var4 += 10.0F;
         var5 -= 2.5F;
         var8 = var1.predict(var3, var2, var4, var5, var6, var7);
         assertEquals(var4 + 10.0F, var8.position.x, 0.01F);
         assertEquals(var5 - 2.5F, var8.position.y, 0.01F);
      }
   }

   @Test
   public void test_predictor() {
      NetworkCharacter var1 = new NetworkCharacter();
      int var2 = 10000;
      short var3 = 200;
      float var4 = 100.0F;
      float var5 = 200.0F;
      float var6 = 1.0F;
      float var7 = -1.0F;
      Transform var8 = var1.predict(var3, var2, var4, var5, var6, var7);
      assertEquals(100.0F, var8.position.x, 0.01F);
      assertEquals(200.0F, var8.position.y, 0.01F);
      var2 += var3;
      var4 += 200.0F;
      var5 += 100.0F;
      var8 = var1.predict(var3, var2, var4, var5, var6, var7);
      assertEquals(500.0F, var8.position.x, 0.01F);
      assertEquals(400.0F, var8.position.y, 0.01F);
      var2 += 10000;
      var4 = 500.0F;
      var5 = 500.0F;
      var8 = var1.predict(var3, var2, var4, var5, var6, var7);
      assertEquals(500.0F, var8.position.x, 0.01F);
      assertEquals(500.0F, var8.position.y, 0.01F);
      var2 += var3;
      var4 = 400.0F;
      var5 = 300.0F;
      var8 = var1.predict(var3, var2, var4, var5, var6, var7);
      assertEquals(300.0F, var8.position.x, 0.01F);
      assertEquals(100.0F, var8.position.y, 0.01F);
   }

   @Test
   public void test_predictor_normal_rotate() {
      NetworkCharacter var1 = new NetworkCharacter();
      short var2 = 10000;
      short var3 = 250;
      float var4 = 100.0F;
      float var5 = 200.0F;
      float var6 = 1.0F;
      float var7 = -1.0F;
      Transform var8 = var1.predict(var3, var2, var4, var5, var6, var7);
      assertEquals(100.0F, var8.position.x, 0.01F);
      assertEquals(200.0F, var8.position.y, 0.01F);

      for (int var9 = 0; var9 < 10; var9++) {
         var2 += var3;
         var4 += 10.0F;
         var5 -= 2.5F;
         var8 = var1.predict(var3, var2, var4, var5, var6, var7);
         assertEquals(var4 + 10.0F, var8.position.x, 0.01F);
         assertEquals(var5 - 2.5F, var8.position.y, 0.01F);
      }

      for (int var12 = 0; var12 < 10; var12++) {
         var2 += var3;
         var4 -= 10.0F;
         var5 += 2.5F;
         var8 = var1.predict(var3, var2, var4, var5, var6, var7);
         assertEquals(var4 - 10.0F, var8.position.x, 0.01F);
         assertEquals(var5 + 2.5F, var8.position.y, 0.01F);
      }
   }

   @Test
   public void test_reconstructor_stay() {
      NetworkCharacter var1 = new NetworkCharacter(0.0F, 100.0F, 0L);
      Transform var2 = var1.transform;
      short var3 = 10000;
      short var4 = 250;
      float var5 = 100.0F;
      float var6 = 200.0F;
      float var7 = 1.0F;
      float var8 = -1.0F;
      var1.updateInterpolationPoint(var3, var5, var6, var7, var8);

      for (int var9 = 0; var9 < 10; var9++) {
         var1.updateInterpolationPoint(var3, var5, var6, var7, var8);
         var2 = var1.reconstruct(var3, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);
         assertEquals(100.0F, var2.position.x, 0.01F);
         assertEquals(200.0F, var2.position.y, 0.01F);
      }

      for (int var10 = 0; var10 < 10; var10++) {
         var3 += var4;
         var1.updateInterpolationPoint(var3, var5, var6, var7, var8);
         var2 = var1.reconstruct(var3, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);
         if (Float.isNaN(var2.position.x)) {
            assertEquals(100.0F, var2.position.x, 0.01F);
         }

         assertEquals(200.0F, var2.position.y, 0.01F);
      }
   }

   @Test
   public void test_reconstructor_normal_go() {
      NetworkCharacter var1 = new NetworkCharacter(0.0F, 100.0F, 0L);
      Transform var2 = var1.transform;
      short var3 = 10000;
      int var4 = var3;
      short var5 = 250;
      float var6 = 100.0F;
      float var7 = 200.0F;
      float var8 = 4.0F;
      float var9 = -1.0F;
      var1.updateInterpolationPoint(var3, var6, var7, var8, var9);

      for (int var10 = 0; var10 < 30; var10++) {
         var3 += var5;
         var6 += 10.0F;
         var7 -= 2.5F;
         var1.updateInterpolationPoint(var3, var6, var7, var8, var9);
         var2 = var1.reconstruct(var4, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);

         for (int var11 = 0; var11 < 5; var11++) {
            var4 += var5 / 5;
            var2 = var1.reconstruct(var4, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);
            System.out
               .print(
                  "transform:(" + var2.position.x + ", " + var2.position.y + ") rotation:(" + var2.rotation.x + ", " + var2.rotation.y + ") t:" + var4 + "\n"
               );
            assertEquals(var6 + (var11 + 1) * 2.0F - 10.0F, var2.position.x, 0.9F);
            assertEquals(var7 - (var11 + 1) * 0.5F + 2.5F, var2.position.y, 0.9F);
         }
      }
   }

   @Test
   public void test_reconstructor_unnormal_go() {
      Transform var1 = new Transform();
      var1.position = new Vector2();
      var1.rotation = new Vector2();
      NetworkCharacter var2 = new NetworkCharacter(0.0F, 100.0F, 0L);
      Transform var3 = var2.transform;
      short var4 = 10000;
      int var5 = var4;
      short var6 = 250;
      float var7 = 100.0F;
      float var8 = 200.0F;
      float var9 = 4.0F;
      float var10 = -1.0F;
      System.out.print("update x:" + var7 + " y:" + var8 + " t:" + var4 + "\n");
      var2.updateInterpolationPoint(var4, var7, var8, var9, var10);
      int var14 = var4 + var6;
      var7 += 10.0F;
      var8 -= 2.5F;
      System.out.print("update x:" + var7 + " y:" + var8 + " t:" + var14 + "\n");
      var2.updateInterpolationPoint(var14, var7, var8, var9, var10);
      var3 = var2.reconstruct(var4, var3.position.x, var3.position.y, var3.rotation.x, var3.rotation.y);

      for (int var11 = 0; var11 < 5; var11++) {
         var5 += var6 / 5;
         var3 = var2.reconstruct(var5, var3.position.x, var3.position.y, var3.rotation.x, var3.rotation.y);
         System.out.print("transform:(" + var3.position.x + ", " + var3.position.y + ")\n");
         assertEquals(var7 + (var11 + 1) * 2.0F - 10.0F, var3.position.x, 1.9F);
         assertEquals(var8 - (var11 + 1) * 0.5F + 2.5F, var3.position.y, 1.5F);
      }

      for (int var17 = 0; var17 < 30; var17++) {
         var14 += var6;
         var7 += 10.0F;
         var8 -= 2.5F;
         System.out.print("update x:" + var7 + " y:" + var8 + " t:" + var14 + "\n");
         var2.updateInterpolationPoint(var14, var7, var8, var9, var10);

         for (int var12 = 0; var12 < 5; var12++) {
            var5 += var6 / 5;
            var3 = var2.reconstruct(var5, var3.position.x, var3.position.y, var3.rotation.x, var3.rotation.y);
            System.out.print("transform:(" + var3.position.x + ", " + var3.position.y + ")\n");
            assertEquals(var7 + (var12 + 1) * 2.0F - 10.0F, var3.position.x, 1.1F);
            assertEquals(var8 - (var12 + 1) * 0.5F + 2.5F, var3.position.y, 1.1F);
            var1.position.set(var3.position);
            var1.rotation.set(var3.rotation);
         }
      }
   }

   @Test
   public void test_all() {
      NetworkCharacter var1 = new NetworkCharacter(0.0F, 100.0F, 0L);
      Transform var2 = var1.transform;
      int var3 = 10000;
      int var4 = var3;
      short var5 = 250;
      float var6 = 100.0F;
      float var7 = 200.0F;
      float var8 = 0.04F;
      float var9 = -0.01F;
      System.out.print("update x:" + var6 + " y:" + var7 + " t:" + var3 + "\n");
      var1.updateInterpolationPoint(var3, var6, var7, var8, var9);
      System.out.print("Normal interpolate\n");

      for (int var10 = 0; var10 < 10; var10++) {
         var3 += var5;
         var6 += 10.0F;
         var7 -= 2.5F;
         System.out.print("update x:" + var6 + " y:" + var7 + " t:" + var3 + "\n");
         var1.updateInterpolationPoint(var3, var6, var7, var8, var9);

         for (int var11 = 0; var11 < 5; var11++) {
            var4 += var5 / 5;
            var2 = var1.reconstruct(var4, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);
            System.out
               .print(
                  "transform:(" + var2.position.x + ", " + var2.position.y + ") rotation:(" + var2.rotation.x + ", " + var2.rotation.y + ") t:" + var4 + "\n"
               );
         }
      }

      System.out.print("Extrapolate\n");

      for (int var18 = 0; var18 < 20; var18++) {
         var4 += var5 / 5;
         var2 = var1.reconstruct(var4, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);
         System.out
            .print("transform:(" + var2.position.x + ", " + var2.position.y + ") rotation:(" + var2.rotation.x + ", " + var2.rotation.y + ") t:" + var4 + "\n");
      }

      System.out.print("Teleport\n");
      var3 += var5 * 10;
      var6 += 100.0F;
      var7 -= 25.0F;
      System.out.print("update x:" + var6 + " y:" + var7 + " t:" + var3 + "\n");
      var1.updateInterpolationPoint(var3, var6, var7, var8, var9);

      for (int var19 = 0; var19 < 30; var19++) {
         var4 += var5 / 5;
         var2 = var1.reconstruct(var4, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);
         System.out
            .print("transform:(" + var2.position.x + ", " + var2.position.y + ") rotation:(" + var2.rotation.x + ", " + var2.rotation.y + ") t:" + var4 + "\n");
      }

      System.out.print("Normal interpolate\n");

      for (int var20 = 0; var20 < 10; var20++) {
         var3 += var5;
         var6 += 10.0F;
         var7 -= 2.5F;
         System.out.print("update x:" + var6 + " y:" + var7 + " t:" + var3 + "\n");
         var1.updateInterpolationPoint(var3, var6, var7, var8, var9);

         for (int var23 = 0; var23 < 5; var23++) {
            var4 += var5 / 5;
            var2 = var1.reconstruct(var4, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);
            System.out
               .print(
                  "transform:(" + var2.position.x + ", " + var2.position.y + ") rotation:(" + var2.rotation.x + ", " + var2.rotation.y + ") t:" + var4 + "\n"
               );
         }
      }

      System.out.print("Extrapolate\n");

      for (int var21 = 0; var21 < 20; var21++) {
         var4 += var5;
         var2 = var1.reconstruct(var4, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);
         System.out
            .print("transform:(" + var2.position.x + ", " + var2.position.y + ") rotation:(" + var2.rotation.x + ", " + var2.rotation.y + ") t:" + var4 + "\n");
      }

      var3 += var5 * 20;
      var6 += 200.0F;
      var7 -= 50.0F;
      System.out.print("Normal interpolate\n");

      for (int var22 = 0; var22 < 10; var22++) {
         var3 += var5;
         var6 += 10.0F;
         var7 -= 2.5F;
         System.out.print("update x:" + var6 + " y:" + var7 + " t:" + var3 + "\n");
         var1.updateInterpolationPoint(var3, var6, var7, var8, var9);

         for (int var24 = 0; var24 < 5; var24++) {
            var4 += var5 / 5;
            var2 = var1.reconstruct(var4, var2.position.x, var2.position.y, var2.rotation.x, var2.rotation.y);
            System.out
               .print(
                  "transform:(" + var2.position.x + ", " + var2.position.y + ") rotation:(" + var2.rotation.x + ", " + var2.rotation.y + ") t:" + var4 + "\n"
               );
         }
      }
   }

   @Test
   public void test_case1() {
      Transform var1 = new Transform();
      var1.position = new Vector2();
      var1.rotation = new Vector2();
      long[] var2 = new long[]{
         982999607L,
         982999623L,
         982999640L,
         982999656L,
         982999674L,
         982999690L,
         982999706L,
         982999723L,
         982999740L,
         982999756L,
         982999773L,
         982999791L,
         982999807L,
         982999823L,
         982999840L,
         982999856L,
         982999872L
      };
      NetworkCharacter var3 = new NetworkCharacter(0.0F, 100.0F, 0L);
      Transform var4 = var3.transform;
      System.out.print("update x:10593.158 y:9952.486 t:982998656\n");
      System.out.print("update x:10593.23 y:9950.746 t:982999872\n");
      var3.updateInterpolationPoint(982998656, 10593.158F, 9952.486F, 0.0F, -0.0014706347F);
      var3.updateInterpolationPoint(982999872, 10593.23F, 9950.746F, 0.0F, -0.0014323471F);
      int var5 = (int)var2[0];

      for (long var9 : var2) {
         var4 = var3.reconstruct((int)var9, var4.position.x, var4.position.y, var4.rotation.x, var4.rotation.y);
         System.out
            .print(
               "transform:("
                  + var4.position.x
                  + ", "
                  + var4.position.y
                  + ") rotation:("
                  + var4.rotation.x
                  + ", "
                  + var4.rotation.y
                  + ") t:"
                  + var9
                  + " t':"
                  + (var9 - var5)
                  + "\n"
            );
         if (var9 > var2[0]) {
         }

         var1.position.set(var4.position);
         var1.rotation.set(var4.rotation);
         var5 = (int)var9;
      }
   }
}
