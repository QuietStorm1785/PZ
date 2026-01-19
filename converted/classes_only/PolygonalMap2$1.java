package zombie.vehicles;

import gnu.trove.procedure.TObjectProcedure;
import zombie.vehicles.PolygonalMap2.Node;

class PolygonalMap2$1 implements TObjectProcedure<Node> {
   PolygonalMap2$1(PolygonalMap2 var1) {
      this.this$0 = var1;
   }

   public boolean execute(Node var1) {
      var1.release();
      return true;
   }
}
