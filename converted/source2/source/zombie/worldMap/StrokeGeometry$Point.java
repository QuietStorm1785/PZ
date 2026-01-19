package zombie.worldMap;

public final class StrokeGeometry$Point {
   double x;
   double y;
   StrokeGeometry$Point next;

   StrokeGeometry$Point() {
      this.x = 0.0;
      this.y = 0.0;
   }

   StrokeGeometry$Point(double var1, double var3) {
      this.x = var1;
      this.y = var3;
   }

   StrokeGeometry$Point set(double var1, double var3) {
      this.x = var1;
      this.y = var3;
      return this;
   }

   StrokeGeometry$Point scalarMult(double var1) {
      this.x *= var1;
      this.y *= var1;
      return this;
   }

   StrokeGeometry$Point perpendicular() {
      double var1 = this.x;
      this.x = -this.y;
      this.y = var1;
      return this;
   }

   StrokeGeometry$Point invert() {
      this.x = -this.x;
      this.y = -this.y;
      return this;
   }

   double length() {
      return Math.sqrt(this.x * this.x + this.y * this.y);
   }

   StrokeGeometry$Point normalize() {
      double var1 = this.length();
      this.x /= var1;
      this.y /= var1;
      return this;
   }

   double angle() {
      return this.y / this.x;
   }

   static double Angle(StrokeGeometry$Point var0, StrokeGeometry$Point var1) {
      return Math.atan2(var1.x - var0.x, var1.y - var0.y);
   }

   static StrokeGeometry$Point Add(StrokeGeometry$Point var0, StrokeGeometry$Point var1) {
      return StrokeGeometry.newPoint(var0.x + var1.x, var0.y + var1.y);
   }

   static StrokeGeometry$Point Sub(StrokeGeometry$Point var0, StrokeGeometry$Point var1) {
      return StrokeGeometry.newPoint(var0.x - var1.x, var0.y - var1.y);
   }

   static StrokeGeometry$Point Middle(StrokeGeometry$Point var0, StrokeGeometry$Point var1) {
      return Add(var0, var1).scalarMult(0.5);
   }
}
