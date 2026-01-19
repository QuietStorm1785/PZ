package zombie.iso;

class WorldMarkers$Point {
   float x;
   float y;

   WorldMarkers$Point(float var1, float var2) {
      this.x = var1;
      this.y = var2;
   }

   public WorldMarkers$Point set(float var1, float var2) {
      this.x = var1;
      this.y = var2;
      return this;
   }

   public boolean notInfinite() {
      return !Float.isInfinite(this.x) && !Float.isInfinite(this.y);
   }

   @Override
   public String toString() {
      return String.format("{%f, %f}", this.x, this.y);
   }
}
