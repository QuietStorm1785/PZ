package zombie.vehicles;

import zombie.vehicles.CircleLineIntersect.Point;
import zombie.vehicles.CircleLineIntersect.RectVector;
import zombie.vehicles.CircleLineIntersect.Vector;
import zombie.vehicles.CircleLineIntersect.VectorMath;

class CircleLineIntersect$PointVector extends Point implements Vector {
   protected double vx = 0.0;
   protected double vy = 0.0;

   public CircleLineIntersect$PointVector(double var1, double var3) {
      this(var1, var3, 0.0, 0.0);
   }

   public CircleLineIntersect$PointVector(double var1, double var3, double var5, double var7) {
      super(var1, var3);
      this.vx = var5;
      this.vy = var7;
   }

   public CircleLineIntersect$PointVector(CircleLineIntersect$PointVector var1) {
      this(var1.getX(), var1.getY(), var1.getvx(), var1.getvy());
   }

   public double getLength() {
      return VectorMath.length(this.vx, this.vy);
   }

   public Vector getVector() {
      return new RectVector(this.vx, this.vy);
   }

   public double getvx() {
      return this.vx;
   }

   public double getvy() {
      return this.vy;
   }

   public double getX1() {
      return this.x;
   }

   public double getX2() {
      return this.x + this.vx;
   }

   public double getY1() {
      return this.y;
   }

   public double getY2() {
      return this.y + this.vy;
   }

   public void setRect(double var1, double var3) {
      this.vx = var1;
      this.vy = var3;
   }
}
