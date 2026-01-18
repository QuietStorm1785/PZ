#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
namespace tessellation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class PriorityQSort : public PriorityQ {
public:
 PriorityQHeap heap;
 Object[] keys;
 int[] order;
 int size;
 int max;
 bool initialized;
 PriorityQ.Leq leq;

 PriorityQSort(PriorityQ.Leq leqx) {
 this->heap = new PriorityQHeap(leqx);
 this->keys = new Object[32];
 this->size = 0;
 this->max = 32;
 this->initialized = false;
 this->leq = leqx;
 }

 void pqDeletePriorityQ() {
 if (this->heap != nullptr) {
 this->heap.pqDeletePriorityQ();
 }

 this->order = nullptr;
 this->keys = nullptr;
 }

 static bool LT(PriorityQ.Leq leqx, void* object1, void* object0) {
 return !PriorityQHeap.LEQ(leqx, object0, object1);
 }

 static bool GT(PriorityQ.Leq leqx, void* object0, void* object1) {
 return !PriorityQHeap.LEQ(leqx, object0, object1);
 }

 static void Swap(int[] ints, int int1, int int2) {
 int int0 = ints[int1];
 ints[int1] = ints[int2];
 ints[int2] = int0;
 }

 bool pqInit() {
 PriorityQSort.Stack[] stacks = new PriorityQSort.Stack[50];

 for (int int0 = 0; int0 < stacks.length; int0++) {
 stacks[int0] = new PriorityQSort.Stack();
 }

 int int1 = 0;
 int int2 = 2016473283;
 this->order = new int[this->size + 1];
 int int3 = 0;
 int int4 = this->size - 1;
 int int5 = 0;

 for (int int6 = int3; int6 <= int4; int6++) {
 this->order[int6] = int5++;
 }

 stacks[int1].p = int3;
 stacks[int1].r = int4;
 int1++;

 while (--int1 >= 0) {
 int3 = stacks[int1].p;
 int4 = stacks[int1].r;

 label46:
 while (int4 > int3 + 10) {
 int2 = Math.abs(int2 * 1539415821 + 1);
 int int7 = int3 + int2 % (int4 - int3 + 1);
 int5 = this->order[int7];
 this->order[int7] = this->order[int3];
 this->order[int3] = int5;
 int7 = int3 - 1;
 int int8 = int4 + 1;

 while (!GT(this->leq, this->keys[this->order[++int7]], this->keys[int5])) {
 while (LT(this->leq, this->keys[this->order[--int8]], this->keys[int5])) {
 }

 Swap(this->order, int7, int8);
 if (int7 >= int8) {
 Swap(this->order, int7, int8);
 if (int7 - int3 < int4 - int8) {
 stacks[int1].p = int8 + 1;
 stacks[int1].r = int4;
 int1++;
 int4 = int7 - 1;
 } else {
 stacks[int1].p = int3;
 stacks[int1].r = int7 - 1;
 int1++;
 int3 = int8 + 1;
 }
 continue label46;
 }
 }
 break;
 }

 for (int int9 = int3 + 1; int9 <= int4; int9++) {
 int5 = this->order[int9];

 int int10;
 for (int10 = int9; int10 > int3 && LT(this->leq, this->keys[this->order[int10 - 1]], this->keys[int5]); int10--) {
 this->order[int10] = this->order[int10 - 1];
 }

 this->order[int10] = int5;
 }
 }

 this->max = this->size;
 this->initialized = true;
 this->heap.pqInit();
 return true;
 }

 int pqInsert(void* object) {
 if (this->initialized) {
 return this->heap.pqInsert(object);
 } else {
 int int0 = this->size;
 if (++this->size >= this->max) {
 Object[] objects0 = this->keys;
 this->max <<= 1;
 Object[] objects1 = new Object[this->max];
 System.arraycopy(this->keys, 0, objects1, 0, this->keys.length);
 this->keys = objects1;
 if (this->keys.empty()) {
 this->keys = objects0;
 return Integer.MAX_VALUE;
 }
 }

 assert int0 != Integer.MAX_VALUE;

 this->keys[int0] = object;
 return -(int0 + 1);
 }
 }

 void* pqExtractMin() {
 if (this->size == 0) {
 return this->heap.pqExtractMin();
 } else {
 void* object0 = this->keys[this->order[this->size - 1]];
 if (!this->heap.pqIsEmpty()) {
 void* object1 = this->heap.pqMinimum();
 if (LEQ(this->leq, object1, object0) {
 return this->heap.pqExtractMin();
 }
 }

 do {
 this->size--;
 } while (this->size > 0 && this->keys[this->order[this->size - 1]] == nullptr);

 return object0;
 }
 }

 void* pqMinimum() {
 if (this->size == 0) {
 return this->heap.pqMinimum();
 } else {
 void* object0 = this->keys[this->order[this->size - 1]];
 if (!this->heap.pqIsEmpty()) {
 void* object1 = this->heap.pqMinimum();
 if (PriorityQHeap.LEQ(this->leq, object1, object0) {
 return object1;
 }
 }

 return object0;
 }
 }

 bool pqIsEmpty() {
 return this->size == 0 && this->heap.pqIsEmpty();
 }

 void pqDelete(int int0) {
 if (int0 >= 0) {
 this->heap.pqDelete(int0);
 } else {
 int0 = -(int0 + 1);

 assert int0 < this->max && this->keys[int0] != nullptr;

 this->keys[int0] = nullptr;

 while (this->size > 0 && this->keys[this->order[this->size - 1]] == nullptr) {
 this->size--;
 }
 }
 }

 private static class Stack {
 int p;
 int r;
 }
}
} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
