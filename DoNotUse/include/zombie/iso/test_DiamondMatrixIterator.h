#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2i.h"
#include "org/junit/Assert.h"
#include "org/junit/Test.h"

namespace zombie {
namespace iso {


class test_DiamondMatrixIterator : public Assert {
public:
    void test3a() {
    uint8_t var1 = 3;
    DiamondMatrixIterator var2 = std::make_shared<DiamondMatrixIterator>(var1);

      for (int var3 = 0; var3 <= var1 * var1; var3++) {
         System.out.println("i=" + var3 + " i2line=" + var2.i2line(var3));
      }

      assertEquals(std::make_shared<Vector2i>(0, 0), var2.i2line(0));
      assertEquals(std::make_shared<Vector2i>(0, 1), var2.i2line(1));
      assertEquals(std::make_shared<Vector2i>(1, 1), var2.i2line(2));
      assertEquals(std::make_shared<Vector2i>(0, 2), var2.i2line(3));
      assertEquals(std::make_shared<Vector2i>(1, 2), var2.i2line(4));
      assertEquals(std::make_shared<Vector2i>(2, 2), var2.i2line(5));
      assertEquals(std::make_shared<Vector2i>(0, 3), var2.i2line(6));
      assertEquals(std::make_shared<Vector2i>(1, 3), var2.i2line(7));
      assertEquals(std::make_shared<Vector2i>(0, 4), var2.i2line(8));
   }

    void test3() {
    uint8_t var1 = 3;
    DiamondMatrixIterator var2 = std::make_shared<DiamondMatrixIterator>(var1);

      for (int var3 = 0; var3 <= var1 * var1; var3++) {
         System.out.println("i=" + var3 + " i2line=" + var2.i2line(var3) + " line2coord=" + var2.line2coord(var2.i2line(var3)));
      }

      assertEquals(std::make_shared<Vector2i>(0, 0), var2.line2coord(var2.i2line(0)));
      assertEquals(std::make_shared<Vector2i>(0, 1), var2.line2coord(var2.i2line(1)));
      assertEquals(std::make_shared<Vector2i>(1, 0), var2.line2coord(var2.i2line(2)));
      assertEquals(std::make_shared<Vector2i>(0, 2), var2.line2coord(var2.i2line(3)));
      assertEquals(std::make_shared<Vector2i>(1, 1), var2.line2coord(var2.i2line(4)));
      assertEquals(std::make_shared<Vector2i>(2, 0), var2.line2coord(var2.i2line(5)));
      assertEquals(std::make_shared<Vector2i>(1, 2), var2.line2coord(var2.i2line(6)));
      assertEquals(std::make_shared<Vector2i>(2, 1), var2.line2coord(var2.i2line(7)));
      assertEquals(std::make_shared<Vector2i>(2, 2), var2.line2coord(var2.i2line(8)));
      assertEquals(nullptr, var2.line2coord(var2.i2line(9)));
   }

    void test3i() {
    uint8_t var1 = 3;
    Vector2i var2 = std::make_shared<Vector2i>();
    DiamondMatrixIterator var3 = std::make_shared<DiamondMatrixIterator>(var1);

      for (int var4 = 0; var4 <= var1 * var1; var4++) {
         var3.next(var2);
         System.out.println("i=" + var4 + " v=" + var2);
      }

      var3.reset();
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(0, 0), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(0, 1), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(1, 0), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(0, 2), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(1, 1), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(2, 0), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(1, 2), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(2, 1), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(2, 2), var2);
      assertEquals(false, var3.next(var2));
   }

    void test4() {
    uint8_t var1 = 4;
    DiamondMatrixIterator var2 = std::make_shared<DiamondMatrixIterator>(var1);

      for (int var3 = 0; var3 <= var1 * var1; var3++) {
         System.out.println("i=" + var3 + " i2line=" + var2.i2line(var3) + " line2coord=" + var2.line2coord(var2.i2line(var3)));
      }

      assertEquals(std::make_shared<Vector2i>(0, 0), var2.line2coord(var2.i2line(0)));
      assertEquals(std::make_shared<Vector2i>(0, 1), var2.line2coord(var2.i2line(1)));
      assertEquals(std::make_shared<Vector2i>(1, 0), var2.line2coord(var2.i2line(2)));
      assertEquals(std::make_shared<Vector2i>(0, 2), var2.line2coord(var2.i2line(3)));
      assertEquals(std::make_shared<Vector2i>(1, 1), var2.line2coord(var2.i2line(4)));
      assertEquals(std::make_shared<Vector2i>(2, 0), var2.line2coord(var2.i2line(5)));
      assertEquals(std::make_shared<Vector2i>(0, 3), var2.line2coord(var2.i2line(6)));
      assertEquals(std::make_shared<Vector2i>(1, 2), var2.line2coord(var2.i2line(7)));
      assertEquals(std::make_shared<Vector2i>(2, 1), var2.line2coord(var2.i2line(8)));
      assertEquals(std::make_shared<Vector2i>(3, 0), var2.line2coord(var2.i2line(9)));
      assertEquals(std::make_shared<Vector2i>(1, 3), var2.line2coord(var2.i2line(10)));
      assertEquals(std::make_shared<Vector2i>(2, 2), var2.line2coord(var2.i2line(11)));
      assertEquals(std::make_shared<Vector2i>(3, 1), var2.line2coord(var2.i2line(12)));
      assertEquals(std::make_shared<Vector2i>(2, 3), var2.line2coord(var2.i2line(13)));
      assertEquals(std::make_shared<Vector2i>(3, 2), var2.line2coord(var2.i2line(14)));
      assertEquals(std::make_shared<Vector2i>(3, 3), var2.line2coord(var2.i2line(15)));
      assertEquals(nullptr, var2.line2coord(var2.i2line(16)));
   }

    void test4i() {
    uint8_t var1 = 4;
    Vector2i var2 = std::make_shared<Vector2i>();
    DiamondMatrixIterator var3 = std::make_shared<DiamondMatrixIterator>(var1);

      for (int var4 = 0; var4 <= var1 * var1; var4++) {
         var3.next(var2);
         System.out.println("i=" + var4 + " v=" + var2);
      }

      var3.reset();
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(0, 0), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(0, 1), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(1, 0), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(0, 2), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(1, 1), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(2, 0), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(0, 3), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(1, 2), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(2, 1), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(3, 0), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(1, 3), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(2, 2), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(3, 1), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(2, 3), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(3, 2), var2);
      assertEquals(true, var3.next(var2));
      assertEquals(std::make_shared<Vector2i>(3, 3), var2);
      assertEquals(false, var3.next(var2));
   }

    void test10() {
    uint8_t var1 = 10;
    DiamondMatrixIterator var2 = std::make_shared<DiamondMatrixIterator>(var1);

      for (int var3 = 0; var3 <= var1 * var1; var3++) {
         System.out.println("i=" + var3 + " i2line=" + var2.i2line(var3) + " line2coord=" + var2.line2coord(var2.i2line(var3)));
      }

    Vector2i var4 = std::make_shared<Vector2i>();

      for (var4.y = 0; var4.y < var1; var4.y++) {
         for (var4.x = 0; var4.x <= var4.y; var4.x++) {
            System.out.println("v=" + var4 + " line2coord=" + var2.line2coord(var4));
         }
      }

      for (var4.y = var1; var4.y <= var1 * 2; var4.y++) {
         for (var4.x = 0; var4.x <= 18 - var4.y; var4.x++) {
            System.out.println("v=" + var4 + " line2coord=" + var2.line2coord(var4));
         }
      }

      assertEquals(std::make_shared<Vector2i>(0, 0), var2.line2coord(var2.i2line(0)));
      assertEquals(std::make_shared<Vector2i>(0, 1), var2.line2coord(var2.i2line(1)));
      assertEquals(std::make_shared<Vector2i>(1, 0), var2.line2coord(var2.i2line(2)));
      assertEquals(std::make_shared<Vector2i>(0, 2), var2.line2coord(var2.i2line(3)));
      assertEquals(std::make_shared<Vector2i>(1, 1), var2.line2coord(var2.i2line(4)));
      assertEquals(std::make_shared<Vector2i>(2, 0), var2.line2coord(var2.i2line(5)));
      assertEquals(std::make_shared<Vector2i>(0, 9), var2.line2coord(var2.i2line(45)));
      assertEquals(std::make_shared<Vector2i>(4, 5), var2.line2coord(var2.i2line(49)));
      assertEquals(std::make_shared<Vector2i>(5, 4), var2.line2coord(var2.i2line(50)));
      assertEquals(std::make_shared<Vector2i>(9, 0), var2.line2coord(var2.i2line(54)));
      assertEquals(std::make_shared<Vector2i>(8, 9), var2.line2coord(var2.i2line(97)));
      assertEquals(std::make_shared<Vector2i>(9, 8), var2.line2coord(var2.i2line(98)));
      assertEquals(std::make_shared<Vector2i>(9, 9), var2.line2coord(var2.i2line(99)));
      assertEquals(nullptr, var2.line2coord(var2.i2line(100)));
      assertEquals(nullptr, var2.line2coord(var2.i2line(34536)));
   }
}
} // namespace iso
} // namespace zombie
