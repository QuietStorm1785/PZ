package zombie.vehicles;

import zombie.vehicles.CircleLineIntersect.Force;

class CircleLineIntersect$ForceCircle extends Force {
   protected double radius;
   protected double radiussq;

   public CircleLineIntersect$ForceCircle(double var1, double var3, double var5, double var7, double var9) {
      super(var1, var3, var5, var7);
      this.radius = var9;
      this.radiussq = var9 * var9;
   }

   double getRadius() {
      return this.radius;
   }

   double getRadiusSq() {
      return this.radiussq;
   }
}
