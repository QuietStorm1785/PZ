#pragma once
#include "astar/datastructures/HashPriorityQueue.h"
#include "org/junit/Assert.h"
#include "org/junit/Test.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace astar {
namespace tests {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DatastructuresTest {
public:
  void hashPriorityQueueTest() {
    class InconsistentComparator implements Comparator<Integer> {
      int compare(int var1, int var2) { return 0; }
    }

    HashPriorityQueue hashPriorityQueue =
        new HashPriorityQueue<>(new InconsistentComparator());
    hashPriorityQueue.add(0, 0);
    hashPriorityQueue.add(1, 1);
    hashPriorityQueue.add(2, 2);
    hashPriorityQueue.add(3, 3);
    hashPriorityQueue.remove(1, 1);
    Assert.assertEquals(true, hashPriorityQueue.contains(0));
    Assert.assertEquals(false, hashPriorityQueue.contains(1));
    Assert.assertEquals(true, hashPriorityQueue.contains(2));
    Assert.assertEquals(true, hashPriorityQueue.contains(3));
    hashPriorityQueue.remove(0, 0);
    Assert.assertEquals(false, hashPriorityQueue.contains(0));
    Assert.assertEquals(true, hashPriorityQueue.contains(2));
    Assert.assertEquals(true, hashPriorityQueue.contains(3));
    hashPriorityQueue.remove(3, 3);
    Assert.assertEquals(true, hashPriorityQueue.contains(2));
    Assert.assertEquals(false, hashPriorityQueue.contains(3));
    hashPriorityQueue.clear();
    hashPriorityQueue.add(0, 0);
    hashPriorityQueue.add(1, 1);
    hashPriorityQueue.add(2, 2);
    hashPriorityQueue.add(3, 3);
    int int0 = (Integer)hashPriorityQueue.poll();
    Assert.assertEquals(0L, hashPriorityQueue.size());
  }
}
} // namespace tests
} // namespace astar
