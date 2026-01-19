#pragma once
#include "org/junit/Assert.h"
#include "org/junit/Test.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class test_ObjectsSyncRequests_getObjectInsertIndex : public Assert {
public:
 void test_getInsertIndex() noexcept{
 long[] longs0 = new long[]{13L, 88L, 51L};
 long[] longs1 = new long[]{8L, 13L, 52L, 21L, 88L, 36L, 51L, 15L};
 assertEquals(0L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 8L);
 assertEquals(-1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 13L);
 assertEquals(1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 52L);
 assertEquals(1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 21L);
 assertEquals(-1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 88L);
 assertEquals(2L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 36L);
 assertEquals(-1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 51L);
 assertEquals(3L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 15L);
 }

 void test_getInsertIndex2() noexcept{
 long[] longs0 = new long[0];
 long[] longs1 = new long[]{81L, 45L, 72L};
 assertEquals(-1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 8L);
 assertEquals(-1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 13L);
 assertEquals(0L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 81L);
 assertEquals(0L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 45L);
 assertEquals(0L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 72L);
 }

 void test_getInsertIndex3() noexcept{
 long[] longs0 = new long[]{71L, 66L, 381L};
 long[] longs1 = new long[]{55L, 81L, 71L, 41L, 66L, 381L, 68L};
 assertEquals(0L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 55L);
 assertEquals(0L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 81L);
 assertEquals(-1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 71L);
 assertEquals(1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 41L);
 assertEquals(-1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 66L);
 assertEquals(
 -1L, ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 381L);
 assertEquals(3L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 68L);
 assertEquals(-1L,
 ObjectsSyncRequests.getObjectInsertIndex(longs0, longs1, 33L);
 }
}
} // namespace iso
} // namespace zombie
