package zombie.vehicles;

class CircleLineIntersect$Point {
   double x;
   double y;

   public static final CircleLineIntersect$Point midpoint(double var0, double var2, double var4, double var6) {
      return new CircleLineIntersect$Point((var0 + var4) / 2.0, (var2 + var6) / 2.0);
   }

   public static final CircleLineIntersect$Point midpoint(CircleLineIntersect$Point var0, CircleLineIntersect$Point var1) {
      return midpoint(var0.getX(), var0.getY(), var1.getX(), var1.getY());
   }

   public CircleLineIntersect$Point(double var1, double var3) {
      if (Double.isNaN(var1) || Double.isInfinite(var1)) {
         var1 = 0.0;
      }

      if (Double.isNaN(var3) || Double.isInfinite(var3)) {
         var3 = 0.0;
      }

      this.x = var1;
      this.y = var3;
   }

   public double getX() {
      return this.x;
   }

   public double getY() {
      return this.y;
   }

   public void setPoint(double var1, double var3) {
      this.x = var1;
      this.y = var3;
   }

   public static double distanceSq(double var0, double var2, double var4, double var6) {
      var0 -= var4;
      var2 -= var6;
      return var0 * var0 + var2 * var2;
   }

   public static double distance(double var0, double var2, double var4, double var6) {
      var0 -= var4;
      var2 -= var6;
      return Math.sqrt(var0 * var0 + var2 * var2);
   }

   public double distanceSq(double var1, double var3) {
      var1 -= this.getX();
      var3 -= this.getY();
      return var1 * var1 + var3 * var3;
   }

   public double distanceSq(CircleLineIntersect$Point var1) {
      double var2 = var1.getX() - this.getX();
      double var4 = var1.getY() - this.getY();
      return var2 * var2 + var4 * var4;
   }

   public double distance(CircleLineIntersect$Point var1) {
      double var2 = var1.getX() - this.getX();
      double var4 = var1.getY() - this.getY();
      return Math.sqrt(var2 * var2 + var4 * var4);
   }
}
