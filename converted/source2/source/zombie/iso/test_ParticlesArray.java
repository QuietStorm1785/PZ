package zombie.iso;

import java.util.Comparator;
import org.junit.Assert;
import org.junit.Test;
import zombie.core.Rand;

public class test_ParticlesArray extends Assert {
   @Test
   public void test_ParticlesArray_functional() {
      ParticlesArray var1 = new ParticlesArray();
      var1.addParticle(new Integer(1));
      var1.addParticle(new Integer(2));
      var1.addParticle(new Integer(3));
      var1.addParticle(new Integer(4));
      var1.addParticle(new Integer(5));
      var1.addParticle(new Integer(6));
      var1.addParticle(new Integer(7));
      var1.addParticle(new Integer(8));
      var1.addParticle(new Integer(9));
      assertEquals(9L, var1.size());
      assertEquals(9L, var1.getCount());

      for (int var2 = 0; var2 < 9; var2++) {
         assertEquals(var2 + 1, ((Integer)var1.get(var2)).intValue());
      }

      var1.deleteParticle(0);
      var1.deleteParticle(1);
      var1.deleteParticle(4);
      var1.deleteParticle(7);
      var1.deleteParticle(8);
      assertEquals(9L, var1.size());
      assertEquals(4L, var1.getCount());
      assertEquals(null, var1.get(0));
      assertEquals(null, var1.get(1));
      assertEquals(3L, ((Integer)var1.get(2)).intValue());
      assertEquals(4L, ((Integer)var1.get(3)).intValue());
      assertEquals(null, var1.get(4));
      assertEquals(6L, ((Integer)var1.get(5)).intValue());
      assertEquals(7L, ((Integer)var1.get(6)).intValue());
      assertEquals(null, var1.get(7));
      assertEquals(null, var1.get(8));
      var1.defragmentParticle();
      assertEquals(9L, var1.size());
      assertEquals(4L, var1.getCount());
      assertEquals(7L, ((Integer)var1.get(0)).intValue());
      assertEquals(6L, ((Integer)var1.get(1)).intValue());
      assertEquals(3L, ((Integer)var1.get(2)).intValue());
      assertEquals(4L, ((Integer)var1.get(3)).intValue());
      assertEquals(null, var1.get(4));
      assertEquals(null, var1.get(5));
      assertEquals(null, var1.get(6));
      assertEquals(null, var1.get(7));
      assertEquals(null, var1.get(8));
      var1.addParticle(new Integer(11));
      var1.addParticle(new Integer(12));
      var1.addParticle(new Integer(13));
      var1.addParticle(new Integer(14));
      var1.addParticle(new Integer(15));
      var1.addParticle(new Integer(16));
      assertEquals(10L, var1.size());
      assertEquals(10L, var1.getCount());
      assertEquals(7L, ((Integer)var1.get(0)).intValue());
      assertEquals(6L, ((Integer)var1.get(1)).intValue());
      assertEquals(3L, ((Integer)var1.get(2)).intValue());
      assertEquals(4L, ((Integer)var1.get(3)).intValue());
      assertEquals(11L, ((Integer)var1.get(4)).intValue());
      assertEquals(12L, ((Integer)var1.get(5)).intValue());
      assertEquals(13L, ((Integer)var1.get(6)).intValue());
      assertEquals(14L, ((Integer)var1.get(7)).intValue());
      assertEquals(15L, ((Integer)var1.get(8)).intValue());
      assertEquals(16L, ((Integer)var1.get(9)).intValue());
      var1.deleteParticle(0);
      var1.deleteParticle(1);
      var1.deleteParticle(4);
      var1.deleteParticle(7);
      var1.deleteParticle(8);
      var1.deleteParticle(9);
      assertEquals(10L, var1.size());
      assertEquals(4L, var1.getCount());
      assertEquals(null, var1.get(0));
      assertEquals(null, var1.get(1));
      assertEquals(3L, ((Integer)var1.get(2)).intValue());
      assertEquals(4L, ((Integer)var1.get(3)).intValue());
      assertEquals(null, var1.get(4));
      assertEquals(12L, ((Integer)var1.get(5)).intValue());
      assertEquals(13L, ((Integer)var1.get(6)).intValue());
      assertEquals(null, var1.get(7));
      assertEquals(null, var1.get(8));
      assertEquals(null, var1.get(9));
      var1.defragmentParticle();
      assertEquals(10L, var1.size());
      assertEquals(4L, var1.getCount());
      assertEquals(13L, ((Integer)var1.get(0)).intValue());
      assertEquals(12L, ((Integer)var1.get(1)).intValue());
      assertEquals(3L, ((Integer)var1.get(2)).intValue());
      assertEquals(4L, ((Integer)var1.get(3)).intValue());
      assertEquals(null, var1.get(4));
      assertEquals(null, var1.get(5));
      assertEquals(null, var1.get(6));
      assertEquals(null, var1.get(7));
      assertEquals(null, var1.get(8));
      assertEquals(null, var1.get(9));
      var1.addParticle(new Integer(21));
      var1.addParticle(new Integer(22));
      assertEquals(10L, var1.size());
      assertEquals(6L, var1.getCount());
      assertEquals(13L, ((Integer)var1.get(0)).intValue());
      assertEquals(12L, ((Integer)var1.get(1)).intValue());
      assertEquals(3L, ((Integer)var1.get(2)).intValue());
      assertEquals(4L, ((Integer)var1.get(3)).intValue());
      assertEquals(21L, ((Integer)var1.get(4)).intValue());
      assertEquals(22L, ((Integer)var1.get(5)).intValue());
      assertEquals(null, var1.get(6));
      assertEquals(null, var1.get(7));
      assertEquals(null, var1.get(8));
      assertEquals(null, var1.get(9));
      assertEquals(6L, var1.addParticle(new Integer(31)));
      assertEquals(7L, var1.addParticle(new Integer(32)));
      assertEquals(8L, var1.addParticle(new Integer(33)));
      assertEquals(9L, var1.addParticle(new Integer(34)));
      assertEquals(10L, var1.addParticle(new Integer(35)));
      assertEquals(11L, var1.size());
      assertEquals(11L, var1.getCount());
      var1.deleteParticle(4);
      assertEquals(11L, var1.size());
      assertEquals(10L, var1.getCount());
      assertEquals(4L, var1.addParticle(new Integer(36)));
   }

   @Test
   public void test_ParticlesArray_Failure() {
      ParticlesArray var1 = new ParticlesArray();
      var1.addParticle(new Integer(1));
      var1.addParticle(new Integer(2));
      var1.addParticle(new Integer(3));
      var1.addParticle(new Integer(4));
      var1.addParticle(new Integer(5));
      var1.addParticle(new Integer(6));
      var1.addParticle(new Integer(7));
      var1.addParticle(new Integer(8));
      var1.addParticle(new Integer(9));
      assertEquals(9L, var1.size());
      assertEquals(9L, var1.getCount());

      for (int var2 = 0; var2 < 9; var2++) {
         assertEquals(var2 + 1, ((Integer)var1.get(var2)).intValue());
      }

      var1.deleteParticle(-1);
      var1.deleteParticle(100);
      var1.addParticle(null);
      assertEquals(9L, var1.size());
      assertEquals(9L, var1.getCount());

      for (int var3 = 0; var3 < 9; var3++) {
         assertEquals(var3 + 1, ((Integer)var1.get(var3)).intValue());
      }

      var1.deleteParticle(3);
      var1.deleteParticle(3);
      var1.deleteParticle(3);
   }

   @Test
   public void test_ParticlesArray_time() {
      ParticlesArray var2 = new ParticlesArray();
      long var3 = System.currentTimeMillis();

      for (int var5 = 0; var5 < 1000000; var5++) {
         var2.addParticle(new Integer(var5));
      }

      long var27 = System.currentTimeMillis();
      System.out.println("Add 1000000 elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      int var1 = 0;
      var3 = System.currentTimeMillis();

      for (int var7 = 0; var7 < 1000000; var7++) {
         if (var2.deleteParticle(var7)) {
            var1++;
         }
      }

      var27 = System.currentTimeMillis();
      System.out.println("Delete " + var1 + " elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      var3 = System.currentTimeMillis();

      for (int var40 = 0; var40 < 1000000; var40++) {
         var2.addParticle(new Integer(var40));
      }

      var27 = System.currentTimeMillis();
      System.out.println("Add 1000000 elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      Rand.init();
      var1 = 0;
      var3 = System.currentTimeMillis();

      for (int var41 = 0; var41 < 500000; var41++) {
         if (var2.deleteParticle(Rand.Next(1000000))) {
            var1++;
         }
      }

      var27 = System.currentTimeMillis();
      System.out.println("Delete random " + var1 + " elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      var3 = System.currentTimeMillis();

      for (int var42 = 0; var42 < 1000000; var42++) {
         var2.addParticle(new Integer(var42));
      }

      var27 = System.currentTimeMillis();
      System.out.println("Add 1000000 elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      Comparator var43 = (var0, var1x) -> var0.compareTo(var1x);
      var3 = System.currentTimeMillis();
      var2.sort(var43);
      var27 = System.currentTimeMillis();
      System.out.println("Sort " + var2.size() + " elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      var1 = 0;
      var3 = System.currentTimeMillis();

      for (int var8 = 0; var8 < 500000; var8++) {
         if (var2.deleteParticle(Rand.Next(1000000))) {
            var1++;
         }
      }

      var27 = System.currentTimeMillis();
      System.out.println("Delete random " + var1 + " elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      var3 = System.currentTimeMillis();
      var2.defragmentParticle();
      var27 = System.currentTimeMillis();
      System.out.println("Defragment " + var2.size() + " elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      var3 = System.currentTimeMillis();

      for (int var44 = 0; var44 < 1000000; var44++) {
         var2.addParticle(new Integer(var44));
      }

      var27 = System.currentTimeMillis();
      System.out.println("Add 1000000 elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      var1 = 0;
      var3 = System.currentTimeMillis();

      for (int var45 = 0; var45 < 500000; var45++) {
         if (var2.deleteParticle(Rand.Next(1000000))) {
            var1++;
         }
      }

      var27 = System.currentTimeMillis();
      System.out.println("Delete random " + var1 + " elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      var3 = System.currentTimeMillis();

      for (int var46 = 0; var46 < 1000000; var46++) {
         var2.addParticle(new Integer(var46));
      }

      var27 = System.currentTimeMillis();
      System.out.println("Add 1000000 elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      var1 = 0;
      var3 = System.currentTimeMillis();

      for (int var47 = 0; var47 < 1000000; var47++) {
         if (var2.deleteParticle(Rand.Next(1000000))) {
            var1++;
         }
      }

      var27 = System.currentTimeMillis();
      System.out.println("Delete random " + var1 + " elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
      var3 = System.currentTimeMillis();
      int var48 = 0;

      for (int var9 = 0; var9 < 100000; var9++) {
         for (int var10 = 0; var10 < var2.size(); var10++) {
            if (var2.get(var10) == null) {
               var2.set(var10, new Integer(var9));
               var48++;
               break;
            }
         }
      }

      var27 = System.currentTimeMillis();
      System.out.println("Simple add " + var48 + " elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
   }
}
