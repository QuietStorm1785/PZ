package zombie.vehicles;

import gnu.trove.procedure.TIntObjectProcedure;
import zombie.vehicles.PolygonalMap2.Node;
import zombie.vehicles.PolygonalMap2.SearchNode;
import zombie.vehicles.PolygonalMap2.VGAStar;

final class PolygonalMap2$VGAStar$InitProc implements TIntObjectProcedure<Node> {
   PolygonalMap2$VGAStar$InitProc(VGAStar var1) {
      this.this$0 = var1;
   }

   public boolean execute(int var1, Node var2) {
      SearchNode var3 = SearchNode.alloc().init(this.this$0, var2);
      var3.square = var2.square;
      this.this$0.squareToNode.put(var1, var3);
      this.this$0.nodeMap.put(var2.ID, var3);
      this.this$0.searchNodes.add(var3);
      return true;
   }
}
