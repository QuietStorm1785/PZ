package zombie.core.booleanrectangles;

import java.util.Comparator;
import zombie.core.booleanrectangles.BooleanRectangleCollection.Point;

class BooleanRectangleCollection$1 implements Comparator<Point> {
   BooleanRectangleCollection$1(BooleanRectangleCollection var1) {
      this.this$0 = var1;
   }

   public int compare(Point var1, Point var2) {
      return var1.Y != var2.Y ? var1.Y - var2.Y : var1.X - var2.X;
   }
}
