package zombie.vehicles;

import zombie.vehicles.CircleLineIntersect.Vector;

class CircleLineIntersect$RectVector implements Vector {
   private double vx;
   private double vy;

   public CircleLineIntersect$RectVector(double var1, double var3) {
      this.vx = var1;
      this.vy = var3;
   }

   public CircleLineIntersect$RectVector(Vector var1) {
      this.setVector(var1);
   }

   public double getLength() {
      return Math.sqrt(Math.abs(this.getvx() * this.getvx() + this.getvy() * this.getvy()));
   }

   public Vector getUnitVector() {
      double var1 = this.getLength();
      return new CircleLineIntersect$RectVector(this.getvx() / var1, this.getvy() / var1);
   }

   public double getvx() {
      return this.vx;
   }

   public double getvy() {
      return this.vy;
   }

   public void setVector(Vector var1) {
      this.vx = var1.getvx();
      this.vy = var1.getvy();
   }
}
