package zombie.iso.weather.fx;

class RainParticle$Point {
   private double origx;
   private double origy;
   private double x;
   private double y;

   private RainParticle$Point(RainParticle var1) {
      this.this$0 = var1;
   }

   public void setOrig(double var1, double var3) {
      this.origx = var1;
      this.origy = var3;
      this.x = var1;
      this.y = var3;
   }

   public void set(double var1, double var3) {
      this.x = var1;
      this.y = var3;
   }
}
