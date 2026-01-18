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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class test_ParticlesArray : public Assert {
public:
 void test_ParticlesArray_functional() {
 ParticlesArray particlesArray = new ParticlesArray();
 particlesArray.addParticle(new Integer(1);
 particlesArray.addParticle(new Integer(2);
 particlesArray.addParticle(new Integer(3);
 particlesArray.addParticle(new Integer(4);
 particlesArray.addParticle(new Integer(5);
 particlesArray.addParticle(new Integer(6);
 particlesArray.addParticle(new Integer(7);
 particlesArray.addParticle(new Integer(8);
 particlesArray.addParticle(new Integer(9);
 assertEquals(9L, particlesArray.size());
 assertEquals(9L, particlesArray.getCount());

 for (int int0 = 0; int0 < 9; int0++) {
 assertEquals(int0 + 1, ((Integer)particlesArray.get(int0).intValue());
 }

 particlesArray.deleteParticle(0);
 particlesArray.deleteParticle(1);
 particlesArray.deleteParticle(4);
 particlesArray.deleteParticle(7);
 particlesArray.deleteParticle(8);
 assertEquals(9L, particlesArray.size());
 assertEquals(4L, particlesArray.getCount());
 assertEquals(nullptr, particlesArray.get(0);
 assertEquals(nullptr, particlesArray.get(1);
 assertEquals(3L, ((Integer)particlesArray.get(2).intValue());
 assertEquals(4L, ((Integer)particlesArray.get(3).intValue());
 assertEquals(nullptr, particlesArray.get(4);
 assertEquals(6L, ((Integer)particlesArray.get(5).intValue());
 assertEquals(7L, ((Integer)particlesArray.get(6).intValue());
 assertEquals(nullptr, particlesArray.get(7);
 assertEquals(nullptr, particlesArray.get(8);
 particlesArray.defragmentParticle();
 assertEquals(9L, particlesArray.size());
 assertEquals(4L, particlesArray.getCount());
 assertEquals(7L, ((Integer)particlesArray.get(0).intValue());
 assertEquals(6L, ((Integer)particlesArray.get(1).intValue());
 assertEquals(3L, ((Integer)particlesArray.get(2).intValue());
 assertEquals(4L, ((Integer)particlesArray.get(3).intValue());
 assertEquals(nullptr, particlesArray.get(4);
 assertEquals(nullptr, particlesArray.get(5);
 assertEquals(nullptr, particlesArray.get(6);
 assertEquals(nullptr, particlesArray.get(7);
 assertEquals(nullptr, particlesArray.get(8);
 particlesArray.addParticle(new Integer(11);
 particlesArray.addParticle(new Integer(12);
 particlesArray.addParticle(new Integer(13);
 particlesArray.addParticle(new Integer(14);
 particlesArray.addParticle(new Integer(15);
 particlesArray.addParticle(new Integer(16);
 assertEquals(10L, particlesArray.size());
 assertEquals(10L, particlesArray.getCount());
 assertEquals(7L, ((Integer)particlesArray.get(0).intValue());
 assertEquals(6L, ((Integer)particlesArray.get(1).intValue());
 assertEquals(3L, ((Integer)particlesArray.get(2).intValue());
 assertEquals(4L, ((Integer)particlesArray.get(3).intValue());
 assertEquals(11L, ((Integer)particlesArray.get(4).intValue());
 assertEquals(12L, ((Integer)particlesArray.get(5).intValue());
 assertEquals(13L, ((Integer)particlesArray.get(6).intValue());
 assertEquals(14L, ((Integer)particlesArray.get(7).intValue());
 assertEquals(15L, ((Integer)particlesArray.get(8).intValue());
 assertEquals(16L, ((Integer)particlesArray.get(9).intValue());
 particlesArray.deleteParticle(0);
 particlesArray.deleteParticle(1);
 particlesArray.deleteParticle(4);
 particlesArray.deleteParticle(7);
 particlesArray.deleteParticle(8);
 particlesArray.deleteParticle(9);
 assertEquals(10L, particlesArray.size());
 assertEquals(4L, particlesArray.getCount());
 assertEquals(nullptr, particlesArray.get(0);
 assertEquals(nullptr, particlesArray.get(1);
 assertEquals(3L, ((Integer)particlesArray.get(2).intValue());
 assertEquals(4L, ((Integer)particlesArray.get(3).intValue());
 assertEquals(nullptr, particlesArray.get(4);
 assertEquals(12L, ((Integer)particlesArray.get(5).intValue());
 assertEquals(13L, ((Integer)particlesArray.get(6).intValue());
 assertEquals(nullptr, particlesArray.get(7);
 assertEquals(nullptr, particlesArray.get(8);
 assertEquals(nullptr, particlesArray.get(9);
 particlesArray.defragmentParticle();
 assertEquals(10L, particlesArray.size());
 assertEquals(4L, particlesArray.getCount());
 assertEquals(13L, ((Integer)particlesArray.get(0).intValue());
 assertEquals(12L, ((Integer)particlesArray.get(1).intValue());
 assertEquals(3L, ((Integer)particlesArray.get(2).intValue());
 assertEquals(4L, ((Integer)particlesArray.get(3).intValue());
 assertEquals(nullptr, particlesArray.get(4);
 assertEquals(nullptr, particlesArray.get(5);
 assertEquals(nullptr, particlesArray.get(6);
 assertEquals(nullptr, particlesArray.get(7);
 assertEquals(nullptr, particlesArray.get(8);
 assertEquals(nullptr, particlesArray.get(9);
 particlesArray.addParticle(new Integer(21);
 particlesArray.addParticle(new Integer(22);
 assertEquals(10L, particlesArray.size());
 assertEquals(6L, particlesArray.getCount());
 assertEquals(13L, ((Integer)particlesArray.get(0).intValue());
 assertEquals(12L, ((Integer)particlesArray.get(1).intValue());
 assertEquals(3L, ((Integer)particlesArray.get(2).intValue());
 assertEquals(4L, ((Integer)particlesArray.get(3).intValue());
 assertEquals(21L, ((Integer)particlesArray.get(4).intValue());
 assertEquals(22L, ((Integer)particlesArray.get(5).intValue());
 assertEquals(nullptr, particlesArray.get(6);
 assertEquals(nullptr, particlesArray.get(7);
 assertEquals(nullptr, particlesArray.get(8);
 assertEquals(nullptr, particlesArray.get(9);
 assertEquals(6L, particlesArray.addParticle(new Integer(31);
 assertEquals(7L, particlesArray.addParticle(new Integer(32);
 assertEquals(8L, particlesArray.addParticle(new Integer(33);
 assertEquals(9L, particlesArray.addParticle(new Integer(34);
 assertEquals(10L, particlesArray.addParticle(new Integer(35);
 assertEquals(11L, particlesArray.size());
 assertEquals(11L, particlesArray.getCount());
 particlesArray.deleteParticle(4);
 assertEquals(11L, particlesArray.size());
 assertEquals(10L, particlesArray.getCount());
 assertEquals(4L, particlesArray.addParticle(new Integer(36);
 }

 void test_ParticlesArray_Failure() {
 ParticlesArray particlesArray = new ParticlesArray();
 particlesArray.addParticle(new Integer(1);
 particlesArray.addParticle(new Integer(2);
 particlesArray.addParticle(new Integer(3);
 particlesArray.addParticle(new Integer(4);
 particlesArray.addParticle(new Integer(5);
 particlesArray.addParticle(new Integer(6);
 particlesArray.addParticle(new Integer(7);
 particlesArray.addParticle(new Integer(8);
 particlesArray.addParticle(new Integer(9);
 assertEquals(9L, particlesArray.size());
 assertEquals(9L, particlesArray.getCount());

 for (int int0 = 0; int0 < 9; int0++) {
 assertEquals(int0 + 1, ((Integer)particlesArray.get(int0).intValue());
 }

 particlesArray.deleteParticle(-1);
 particlesArray.deleteParticle(100);
 particlesArray.addParticle(nullptr);
 assertEquals(9L, particlesArray.size());
 assertEquals(9L, particlesArray.getCount());

 for (int int1 = 0; int1 < 9; int1++) {
 assertEquals(int1 + 1, ((Integer)particlesArray.get(int1).intValue());
 }

 particlesArray.deleteParticle(3);
 particlesArray.deleteParticle(3);
 particlesArray.deleteParticle(3);
 }

 void test_ParticlesArray_time() {
 ParticlesArray particlesArray = new ParticlesArray();
 long long0 = System.currentTimeMillis();

 for (int int0 = 0; int0 < 1000000; int0++) {
 particlesArray.addParticle(new Integer(int0);
 }

 long long1 = System.currentTimeMillis();
 System.out.println("Add 1000000 elements = " + (long1 - long0) + " ms (size=" + particlesArray.size() + ", count=" + particlesArray.getCount() + ")");
 int int1 = 0;
 long0 = System.currentTimeMillis();

 for (int int2 = 0; int2 < 1000000; int2++) {
 if (particlesArray.deleteParticle(int2) {
 int1++;
 }
 }

 long1 = System.currentTimeMillis();
 System.out
 .println("Delete " + int1 + " elements = " + (long1 - long0) + " ms (size=" + particlesArray.size() + ", count=" + particlesArray.getCount() + ")");
 long0 = System.currentTimeMillis();

 for (int int3 = 0; int3 < 1000000; int3++) {
 particlesArray.addParticle(new Integer(int3);
 }

 long1 = System.currentTimeMillis();
 System.out.println("Add 1000000 elements = " + (long1 - long0) + " ms (size=" + particlesArray.size() + ", count=" + particlesArray.getCount() + ")");
 Rand.init();
 int1 = 0;
 long0 = System.currentTimeMillis();

 for (int int4 = 0; int4 < 500000; int4++) {
 if (particlesArray.deleteParticle(Rand.Next(1000000) {
 int1++;
 }
 }

 long1 = System.currentTimeMillis();
 System.out
 .println(
 "Delete random "
 + int1
 + " elements = "
 + (long1 - long0)
 + " ms (size="
 + particlesArray.size()
 + ", count="
 + particlesArray.getCount()
 + ")"
 );
 long0 = System.currentTimeMillis();

 for (int int5 = 0; int5 < 1000000; int5++) {
 particlesArray.addParticle(new Integer(int5);
 }

 long1 = System.currentTimeMillis();
 System.out.println("Add 1000000 elements = " + (long1 - long0) + " ms (size=" + particlesArray.size() + ", count=" + particlesArray.getCount() + ")");
 Comparator comparator = (integer0, integer1) -> integer0.compareTo(integer1);
 long0 = System.currentTimeMillis();
 particlesArray.sort(comparator);
 long1 = System.currentTimeMillis();
 System.out
 .println(
 "Sort "
 + particlesArray.size()
 + " elements = "
 + (long1 - long0)
 + " ms (size="
 + particlesArray.size()
 + ", count="
 + particlesArray.getCount()
 + ")"
 );
 int1 = 0;
 long0 = System.currentTimeMillis();

 for (int int6 = 0; int6 < 500000; int6++) {
 if (particlesArray.deleteParticle(Rand.Next(1000000) {
 int1++;
 }
 }

 long1 = System.currentTimeMillis();
 System.out
 .println(
 "Delete random "
 + int1
 + " elements = "
 + (long1 - long0)
 + " ms (size="
 + particlesArray.size()
 + ", count="
 + particlesArray.getCount()
 + ")"
 );
 long0 = System.currentTimeMillis();
 particlesArray.defragmentParticle();
 long1 = System.currentTimeMillis();
 System.out
 .println(
 "Defragment "
 + particlesArray.size()
 + " elements = "
 + (long1 - long0)
 + " ms (size="
 + particlesArray.size()
 + ", count="
 + particlesArray.getCount()
 + ")"
 );
 long0 = System.currentTimeMillis();

 for (int int7 = 0; int7 < 1000000; int7++) {
 particlesArray.addParticle(new Integer(int7);
 }

 long1 = System.currentTimeMillis();
 System.out.println("Add 1000000 elements = " + (long1 - long0) + " ms (size=" + particlesArray.size() + ", count=" + particlesArray.getCount() + ")");
 int1 = 0;
 long0 = System.currentTimeMillis();

 for (int int8 = 0; int8 < 500000; int8++) {
 if (particlesArray.deleteParticle(Rand.Next(1000000) {
 int1++;
 }
 }

 long1 = System.currentTimeMillis();
 System.out
 .println(
 "Delete random "
 + int1
 + " elements = "
 + (long1 - long0)
 + " ms (size="
 + particlesArray.size()
 + ", count="
 + particlesArray.getCount()
 + ")"
 );
 long0 = System.currentTimeMillis();

 for (int int9 = 0; int9 < 1000000; int9++) {
 particlesArray.addParticle(new Integer(int9);
 }

 long1 = System.currentTimeMillis();
 System.out.println("Add 1000000 elements = " + (long1 - long0) + " ms (size=" + particlesArray.size() + ", count=" + particlesArray.getCount() + ")");
 int1 = 0;
 long0 = System.currentTimeMillis();

 for (int int10 = 0; int10 < 1000000; int10++) {
 if (particlesArray.deleteParticle(Rand.Next(1000000) {
 int1++;
 }
 }

 long1 = System.currentTimeMillis();
 System.out
 .println(
 "Delete random "
 + int1
 + " elements = "
 + (long1 - long0)
 + " ms (size="
 + particlesArray.size()
 + ", count="
 + particlesArray.getCount()
 + ")"
 );
 long0 = System.currentTimeMillis();
 int int11 = 0;

 for (int int12 = 0; int12 < 100000; int12++) {
 for (int int13 = 0; int13 < particlesArray.size(); int13++) {
 if (particlesArray.get(int13) == nullptr) {
 particlesArray.set(int13, new Integer(int12);
 int11++;
 break;
 }
 }
 }

 long1 = System.currentTimeMillis();
 System.out
 .println(
 "Simple add " + int11 + " elements = " + (long1 - long0) + " ms (size=" + particlesArray.size() + ", count=" + particlesArray.getCount() + ")"
 );
 }
}
} // namespace iso
} // namespace zombie
