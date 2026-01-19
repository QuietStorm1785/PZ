package zombie.vehicles;

import astar.IGoalNode;
import astar.ISearchNode;
import zombie.vehicles.PolygonalMap2.SearchNode;

final class PolygonalMap2$GoalNode implements IGoalNode {
   SearchNode searchNode;

   private PolygonalMap2$GoalNode() {
   }

   PolygonalMap2$GoalNode init(SearchNode var1) {
      this.searchNode = var1;
      return this;
   }

   public boolean inGoal(ISearchNode var1) {
      if (this.searchNode.tx != -1) {
         SearchNode var2 = (SearchNode)var1;
         int var3 = (int)var2.getX();
         int var4 = (int)var2.getY();
         if (var3 % 10 == 0 && PolygonalMap2.instance.getChunkFromSquarePos(var3 - 1, var4) == null) {
            return true;
         } else if (var3 % 10 == 9 && PolygonalMap2.instance.getChunkFromSquarePos(var3 + 1, var4) == null) {
            return true;
         } else {
            return var4 % 10 == 0 && PolygonalMap2.instance.getChunkFromSquarePos(var3, var4 - 1) == null
               ? true
               : var4 % 10 == 9 && PolygonalMap2.instance.getChunkFromSquarePos(var3, var4 + 1) == null;
         }
      } else {
         return var1 == this.searchNode;
      }
   }
}
