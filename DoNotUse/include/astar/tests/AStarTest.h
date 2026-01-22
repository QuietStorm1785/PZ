#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/AStar.h"
#include "astar/ISearchNode.h"
#include "org/junit/Assert.h"
#include "org/junit/Test.h"

namespace astar {
namespace tests {


class AStarTest {
public:
    void SearchNodeTest2D() {
    GoalNode2D var1 = std::make_shared<GoalNode2D>(3, 3);
    SearchNode2D var2 = std::make_shared<SearchNode2D>(1, 1, nullptr, var1);
    std::vector var3 = std::make_shared<AStar>().shortestPath(var2, var1);
      Assert.assertEquals(var3.size(), 5L);
   }

    void SearchNodeCityTest() {
    SearchNodeCity var1 = std::make_shared<SearchNodeCity>("SaarbrÃ¼cken");
    std::vector var2 = std::make_shared<AStar>().shortestPath(var1, std::make_shared<GoalNodeCity>("WÃ¼rzburg"));
    double var3 = 1.0E-5;
      Assert.assertEquals(((ISearchNode)var2.get(0)).f(), 222.0, var3);
      Assert.assertEquals(((ISearchNode)var2.get(1)).f(), 228.0, var3);
      Assert.assertEquals(((ISearchNode)var2.get(2)).f(), 269.0, var3);
      Assert.assertEquals(((ISearchNode)var2.get(3)).f(), 289.0, var3);
      Assert.assertEquals(var2, "[SaarbrÃ¼cken,f:222.0, Kaiserslautern,f:228.0, Frankfurt,f:269.0, WÃ¼rzburg,f:289.0]");
   }
}
} // namespace tests
} // namespace astar
