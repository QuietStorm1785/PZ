#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/junit/Assert.h"
#include "org/junit/Test.h"
#include "zombie/core/Rand.h"
#include <algorithm>

namespace zombie {
namespace iso {


class test_ParticlesArray : public Assert {
public:
    void test_ParticlesArray_functional() {
    ParticlesArray var1 = std::make_shared<ParticlesArray>();
      var1.addParticle(std::make_shared<int>(1));
      var1.addParticle(std::make_shared<int>(2));
      var1.addParticle(std::make_shared<int>(3));
      var1.addParticle(std::make_shared<int>(4));
      var1.addParticle(std::make_shared<int>(5));
      var1.addParticle(std::make_shared<int>(6));
      var1.addParticle(std::make_shared<int>(7));
      var1.addParticle(std::make_shared<int>(8));
      var1.addParticle(std::make_shared<int>(9));
      assertEquals(9L, var1.size());
      assertEquals(9L, var1.getCount());

      for (int var2 = 0; var2 < 9; var2++) {
         assertEquals(var2 + 1, ((int)var1.get(var2)).intValue());
      }

      var1.deleteParticle(0);
      var1.deleteParticle(1);
      var1.deleteParticle(4);
      var1.deleteParticle(7);
      var1.deleteParticle(8);
      assertEquals(9L, var1.size());
      assertEquals(4L, var1.getCount());
      assertEquals(nullptr, var1.get(0));
      assertEquals(nullptr, var1.get(1));
      assertEquals(3L, ((int)var1.get(2)).intValue());
      assertEquals(4L, ((int)var1.get(3)).intValue());
      assertEquals(nullptr, var1.get(4));
      assertEquals(6L, ((int)var1.get(5)).intValue());
      assertEquals(7L, ((int)var1.get(6)).intValue());
      assertEquals(nullptr, var1.get(7));
      assertEquals(nullptr, var1.get(8));
      var1.defragmentParticle();
      assertEquals(9L, var1.size());
      assertEquals(4L, var1.getCount());
      assertEquals(7L, ((int)var1.get(0)).intValue());
      assertEquals(6L, ((int)var1.get(1)).intValue());
      assertEquals(3L, ((int)var1.get(2)).intValue());
      assertEquals(4L, ((int)var1.get(3)).intValue());
      assertEquals(nullptr, var1.get(4));
      assertEquals(nullptr, var1.get(5));
      assertEquals(nullptr, var1.get(6));
      assertEquals(nullptr, var1.get(7));
      assertEquals(nullptr, var1.get(8));
      var1.addParticle(std::make_shared<int>(11));
      var1.addParticle(std::make_shared<int>(12));
      var1.addParticle(std::make_shared<int>(13));
      var1.addParticle(std::make_shared<int>(14));
      var1.addParticle(std::make_shared<int>(15));
      var1.addParticle(std::make_shared<int>(16));
      assertEquals(10L, var1.size());
      assertEquals(10L, var1.getCount());
      assertEquals(7L, ((int)var1.get(0)).intValue());
      assertEquals(6L, ((int)var1.get(1)).intValue());
      assertEquals(3L, ((int)var1.get(2)).intValue());
      assertEquals(4L, ((int)var1.get(3)).intValue());
      assertEquals(11L, ((int)var1.get(4)).intValue());
      assertEquals(12L, ((int)var1.get(5)).intValue());
      assertEquals(13L, ((int)var1.get(6)).intValue());
      assertEquals(14L, ((int)var1.get(7)).intValue());
      assertEquals(15L, ((int)var1.get(8)).intValue());
      assertEquals(16L, ((int)var1.get(9)).intValue());
      var1.deleteParticle(0);
      var1.deleteParticle(1);
      var1.deleteParticle(4);
      var1.deleteParticle(7);
      var1.deleteParticle(8);
      var1.deleteParticle(9);
      assertEquals(10L, var1.size());
      assertEquals(4L, var1.getCount());
      assertEquals(nullptr, var1.get(0));
      assertEquals(nullptr, var1.get(1));
      assertEquals(3L, ((int)var1.get(2)).intValue());
      assertEquals(4L, ((int)var1.get(3)).intValue());
      assertEquals(nullptr, var1.get(4));
      assertEquals(12L, ((int)var1.get(5)).intValue());
      assertEquals(13L, ((int)var1.get(6)).intValue());
      assertEquals(nullptr, var1.get(7));
      assertEquals(nullptr, var1.get(8));
      assertEquals(nullptr, var1.get(9));
      var1.defragmentParticle();
      assertEquals(10L, var1.size());
      assertEquals(4L, var1.getCount());
      assertEquals(13L, ((int)var1.get(0)).intValue());
      assertEquals(12L, ((int)var1.get(1)).intValue());
      assertEquals(3L, ((int)var1.get(2)).intValue());
      assertEquals(4L, ((int)var1.get(3)).intValue());
      assertEquals(nullptr, var1.get(4));
      assertEquals(nullptr, var1.get(5));
      assertEquals(nullptr, var1.get(6));
      assertEquals(nullptr, var1.get(7));
      assertEquals(nullptr, var1.get(8));
      assertEquals(nullptr, var1.get(9));
      var1.addParticle(std::make_shared<int>(21));
      var1.addParticle(std::make_shared<int>(22));
      assertEquals(10L, var1.size());
      assertEquals(6L, var1.getCount());
      assertEquals(13L, ((int)var1.get(0)).intValue());
      assertEquals(12L, ((int)var1.get(1)).intValue());
      assertEquals(3L, ((int)var1.get(2)).intValue());
      assertEquals(4L, ((int)var1.get(3)).intValue());
      assertEquals(21L, ((int)var1.get(4)).intValue());
      assertEquals(22L, ((int)var1.get(5)).intValue());
      assertEquals(nullptr, var1.get(6));
      assertEquals(nullptr, var1.get(7));
      assertEquals(nullptr, var1.get(8));
      assertEquals(nullptr, var1.get(9));
      assertEquals(6L, var1.addParticle(std::make_shared<int>(31)));
      assertEquals(7L, var1.addParticle(std::make_shared<int>(32)));
      assertEquals(8L, var1.addParticle(std::make_shared<int>(33)));
      assertEquals(9L, var1.addParticle(std::make_shared<int>(34)));
      assertEquals(10L, var1.addParticle(std::make_shared<int>(35)));
      assertEquals(11L, var1.size());
      assertEquals(11L, var1.getCount());
      var1.deleteParticle(4);
      assertEquals(11L, var1.size());
      assertEquals(10L, var1.getCount());
      assertEquals(4L, var1.addParticle(std::make_shared<int>(36)));
   }

    void test_ParticlesArray_Failure() {
    ParticlesArray var1 = std::make_shared<ParticlesArray>();
      var1.addParticle(std::make_shared<int>(1));
      var1.addParticle(std::make_shared<int>(2));
      var1.addParticle(std::make_shared<int>(3));
      var1.addParticle(std::make_shared<int>(4));
      var1.addParticle(std::make_shared<int>(5));
      var1.addParticle(std::make_shared<int>(6));
      var1.addParticle(std::make_shared<int>(7));
      var1.addParticle(std::make_shared<int>(8));
      var1.addParticle(std::make_shared<int>(9));
      assertEquals(9L, var1.size());
      assertEquals(9L, var1.getCount());

      for (int var2 = 0; var2 < 9; var2++) {
         assertEquals(var2 + 1, ((int)var1.get(var2)).intValue());
      }

      var1.deleteParticle(-1);
      var1.deleteParticle(100);
      var1.addParticle(nullptr);
      assertEquals(9L, var1.size());
      assertEquals(9L, var1.getCount());

      for (int var3 = 0; var3 < 9; var3++) {
         assertEquals(var3 + 1, ((int)var1.get(var3)).intValue());
      }

      var1.deleteParticle(3);
      var1.deleteParticle(3);
      var1.deleteParticle(3);
   }

    void test_ParticlesArray_time() {
    ParticlesArray var2 = std::make_shared<ParticlesArray>();
    long var3 = System.currentTimeMillis();

      for (int var5 = 0; var5 < 1000000; var5++) {
         var2.addParticle(std::make_shared<int>(var5));
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
         var2.addParticle(std::make_shared<int>(var40));
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
         var2.addParticle(std::make_shared<int>(var42));
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
         var2.addParticle(std::make_shared<int>(var44));
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
         var2.addParticle(std::make_shared<int>(var46));
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
            if (var2.get(var10) == nullptr) {
               var2.set(var10, std::make_shared<int>(var9));
               var48++;
               break;
            }
         }
      }

      var27 = System.currentTimeMillis();
      System.out.println("Simple add " + var48 + " elements = " + (var27 - var3) + " ms (size=" + var2.size() + ", count=" + var2.getCount() + ")");
   }
}
} // namespace iso
} // namespace zombie
