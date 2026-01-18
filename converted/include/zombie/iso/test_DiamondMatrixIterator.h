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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class test_DiamondMatrixIterator : public Assert {
public:
 void test3a() {
 uint8_t byte0 = 3;
 DiamondMatrixIterator diamondMatrixIterator = new DiamondMatrixIterator(byte0);

 for (int int0 = 0; int0 <= byte0 * byte0; int0++) {
 System.out.println("i=" + int0 + " i2line=" + diamondMatrixIterator.i2line(int0);
 }

 assertEquals(new Vector2i(0, 0), diamondMatrixIterator.i2line(0);
 assertEquals(new Vector2i(0, 1), diamondMatrixIterator.i2line(1);
 assertEquals(new Vector2i(1, 1), diamondMatrixIterator.i2line(2);
 assertEquals(new Vector2i(0, 2), diamondMatrixIterator.i2line(3);
 assertEquals(new Vector2i(1, 2), diamondMatrixIterator.i2line(4);
 assertEquals(new Vector2i(2, 2), diamondMatrixIterator.i2line(5);
 assertEquals(new Vector2i(0, 3), diamondMatrixIterator.i2line(6);
 assertEquals(new Vector2i(1, 3), diamondMatrixIterator.i2line(7);
 assertEquals(new Vector2i(0, 4), diamondMatrixIterator.i2line(8);
 }

 void test3() {
 uint8_t byte0 = 3;
 DiamondMatrixIterator diamondMatrixIterator = new DiamondMatrixIterator(byte0);

 for (int int0 = 0; int0 <= byte0 * byte0; int0++) {
 System.out
 .println(
 "i="
 + int0
 + " i2line="
 + diamondMatrixIterator.i2line(int0)
 + " line2coord="
 + diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(int0)
 );
 }

 assertEquals(new Vector2i(0, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(0);
 assertEquals(new Vector2i(0, 1), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(1);
 assertEquals(new Vector2i(1, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(2);
 assertEquals(new Vector2i(0, 2), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(3);
 assertEquals(new Vector2i(1, 1), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(4);
 assertEquals(new Vector2i(2, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(5);
 assertEquals(new Vector2i(1, 2), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(6);
 assertEquals(new Vector2i(2, 1), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(7);
 assertEquals(new Vector2i(2, 2), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(8);
 assertEquals(nullptr, diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(9);
 }

 void test3i() {
 uint8_t byte0 = 3;
 Vector2i vector2i = new Vector2i();
 DiamondMatrixIterator diamondMatrixIterator = new DiamondMatrixIterator(byte0);

 for (int int0 = 0; int0 <= byte0 * byte0; int0++) {
 diamondMatrixIterator.next(vector2i);
 System.out.println("i=" + int0 + " v=" + vector2i);
 }

 diamondMatrixIterator.reset();
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(0, 0), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(0, 1), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(1, 0), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(0, 2), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(1, 1), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(2, 0), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(1, 2), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(2, 1), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(2, 2), vector2i);
 assertEquals(false, diamondMatrixIterator.next(vector2i);
 }

 void test4() {
 uint8_t byte0 = 4;
 DiamondMatrixIterator diamondMatrixIterator = new DiamondMatrixIterator(byte0);

 for (int int0 = 0; int0 <= byte0 * byte0; int0++) {
 System.out
 .println(
 "i="
 + int0
 + " i2line="
 + diamondMatrixIterator.i2line(int0)
 + " line2coord="
 + diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(int0)
 );
 }

 assertEquals(new Vector2i(0, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(0);
 assertEquals(new Vector2i(0, 1), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(1);
 assertEquals(new Vector2i(1, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(2);
 assertEquals(new Vector2i(0, 2), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(3);
 assertEquals(new Vector2i(1, 1), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(4);
 assertEquals(new Vector2i(2, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(5);
 assertEquals(new Vector2i(0, 3), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(6);
 assertEquals(new Vector2i(1, 2), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(7);
 assertEquals(new Vector2i(2, 1), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(8);
 assertEquals(new Vector2i(3, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(9);
 assertEquals(new Vector2i(1, 3), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(10);
 assertEquals(new Vector2i(2, 2), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(11);
 assertEquals(new Vector2i(3, 1), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(12);
 assertEquals(new Vector2i(2, 3), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(13);
 assertEquals(new Vector2i(3, 2), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(14);
 assertEquals(new Vector2i(3, 3), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(15);
 assertEquals(nullptr, diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(16);
 }

 void test4i() {
 uint8_t byte0 = 4;
 Vector2i vector2i = new Vector2i();
 DiamondMatrixIterator diamondMatrixIterator = new DiamondMatrixIterator(byte0);

 for (int int0 = 0; int0 <= byte0 * byte0; int0++) {
 diamondMatrixIterator.next(vector2i);
 System.out.println("i=" + int0 + " v=" + vector2i);
 }

 diamondMatrixIterator.reset();
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(0, 0), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(0, 1), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(1, 0), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(0, 2), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(1, 1), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(2, 0), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(0, 3), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(1, 2), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(2, 1), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(3, 0), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(1, 3), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(2, 2), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(3, 1), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(2, 3), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(3, 2), vector2i);
 assertEquals(true, diamondMatrixIterator.next(vector2i);
 assertEquals(new Vector2i(3, 3), vector2i);
 assertEquals(false, diamondMatrixIterator.next(vector2i);
 }

 void test10() {
 uint8_t byte0 = 10;
 DiamondMatrixIterator diamondMatrixIterator = new DiamondMatrixIterator(byte0);

 for (int int0 = 0; int0 <= byte0 * byte0; int0++) {
 System.out
 .println(
 "i="
 + int0
 + " i2line="
 + diamondMatrixIterator.i2line(int0)
 + " line2coord="
 + diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(int0)
 );
 }

 Vector2i vector2i = new Vector2i();

 for (vector2i.y = 0; vector2i.y < byte0; vector2i.y++) {
 for (vector2i.x = 0; vector2i.x <= vector2i.y; vector2i.x++) {
 System.out.println("v=" + vector2i + " line2coord=" + diamondMatrixIterator.line2coord(vector2i);
 }
 }

 for (vector2i.y = byte0; vector2i.y <= byte0 * 2; vector2i.y++) {
 for (vector2i.x = 0; vector2i.x <= 18 - vector2i.y; vector2i.x++) {
 System.out.println("v=" + vector2i + " line2coord=" + diamondMatrixIterator.line2coord(vector2i);
 }
 }

 assertEquals(new Vector2i(0, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(0);
 assertEquals(new Vector2i(0, 1), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(1);
 assertEquals(new Vector2i(1, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(2);
 assertEquals(new Vector2i(0, 2), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(3);
 assertEquals(new Vector2i(1, 1), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(4);
 assertEquals(new Vector2i(2, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(5);
 assertEquals(new Vector2i(0, 9), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(45);
 assertEquals(new Vector2i(4, 5), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(49);
 assertEquals(new Vector2i(5, 4), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(50);
 assertEquals(new Vector2i(9, 0), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(54);
 assertEquals(new Vector2i(8, 9), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(97);
 assertEquals(new Vector2i(9, 8), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(98);
 assertEquals(new Vector2i(9, 9), diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(99);
 assertEquals(nullptr, diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(100);
 assertEquals(nullptr, diamondMatrixIterator.line2coord(diamondMatrixIterator.i2line(34536);
 }
}
} // namespace iso
} // namespace zombie
