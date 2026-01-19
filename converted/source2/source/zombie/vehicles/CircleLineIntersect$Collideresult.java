package zombie.vehicles;

import java.util.ArrayList;
import zombie.vehicles.CircleLineIntersect.Collideclassindex;
import zombie.vehicles.CircleLineIntersect.PointVector;

class CircleLineIntersect$Collideresult {
   protected PointVector[] resultants;
   protected ArrayList<Integer> collidelist;
   protected Collideclassindex[] collideinto;
   protected double[] timepassed;
   protected double[] collidetime;
   protected boolean[] modified;

   public CircleLineIntersect$Collideresult(PointVector[] var1, Collideclassindex[] var2, ArrayList<Integer> var3, double[] var4, double[] var5, boolean[] var6) {
      this.resultants = var1;
      this.collideinto = var2;
      this.collidelist = var3;
      this.timepassed = var4;
      this.collidetime = var5;
      this.modified = var6;
   }

   @Override
   public String toString() {
      return this.collidelist.toString();
   }
}
