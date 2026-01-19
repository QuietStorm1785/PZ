package zombie.vehicles;

public final class PolygonalMap2$Point {
   public int x;
   public int y;

   PolygonalMap2$Point init(int var1, int var2) {
      this.x = var1;
      this.y = var2;
      return this;
   }

   @Override
   public boolean equals(Object var1) {
      return var1 instanceof PolygonalMap2$Point && ((PolygonalMap2$Point)var1).x == this.x && ((PolygonalMap2$Point)var1).y == this.y;
   }
}
