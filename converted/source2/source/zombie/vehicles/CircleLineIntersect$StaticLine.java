package zombie.vehicles;

import zombie.vehicles.CircleLineIntersect.Point;

class CircleLineIntersect$StaticLine extends Point {
   double x2;
   double y2;

   public CircleLineIntersect$StaticLine(double var1, double var3, double var5, double var7) {
      super(var1, var3);
      this.x2 = var5;
      this.y2 = var7;
   }

   public Point getP1() {
      return new Point(this.getX1(), this.getY1());
   }

   public Point getP2() {
      return new Point(this.getX2(), this.getY2());
   }

   public double getX1() {
      return this.x;
   }

   public double getX2() {
      return this.x2;
   }

   public double getY1() {
      return this.y;
   }

   public double getY2() {
      return this.y2;
   }
}
