package zombie.core.booleanrectangles;

import zombie.core.booleanrectangles.BooleanRectangleCollection.Point;

public class BooleanRectangleCollection$Line {
   public Point Start;
   public Point End;

   public BooleanRectangleCollection$Line(BooleanRectangleCollection var1, Point var2, Point var3) {
      this.this$0 = var1;
      this.Start = new Point();
      this.End = new Point();
      this.Start.X = var2.X;
      this.Start.Y = var2.Y;
      this.End.X = var3.X;
      this.End.Y = var3.Y;
   }
}
