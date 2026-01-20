#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/datastructures/HashPriorityQueue.h"
#include "astar/tests/DatastructuresTest/1InconsistentComparator.h"
#include "org/junit/Assert.h"
#include "org/junit/Test.h"

namespace astar {
namespace tests {


class DatastructuresTest {
public:
    void hashPriorityQueueTest() {
    HashPriorityQueue var1 = std::make_shared<HashPriorityQueue>(std::make_shared<1InconsistentComparator>(this));
      var1.push_back(0, 0);
      var1.push_back(1, 1);
      var1.push_back(2, 2);
      var1.push_back(3, 3);
      var1.remove(1, 1);
      Assert.assertEquals(true, var1.contains(0));
      Assert.assertEquals(false, var1.contains(1));
      Assert.assertEquals(true, var1.contains(2));
      Assert.assertEquals(true, var1.contains(3));
      var1.remove(0, 0);
      Assert.assertEquals(false, var1.contains(0));
      Assert.assertEquals(true, var1.contains(2));
      Assert.assertEquals(true, var1.contains(3));
      var1.remove(3, 3);
      Assert.assertEquals(true, var1.contains(2));
      Assert.assertEquals(false, var1.contains(3));
      var1.clear();
      var1.push_back(0, 0);
      var1.push_back(1, 1);
      var1.push_back(2, 2);
      var1.push_back(3, 3);
    int var2 = (int)var1.poll();
      Assert.assertEquals(0L, var1.size());
   }
}
} // namespace tests
} // namespace astar
