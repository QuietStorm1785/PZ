package zombie.iso;

import zombie.iso.WorldMarkers.Point;

class WorldMarkers$Line {
   Point s;
   Point e;

   WorldMarkers$Line(Point var1, Point var2) {
      this.s = var1;
      this.e = var2;
   }

   @Override
   public String toString() {
      return String.format("{s: %s, e: %s}", this.s.toString(), this.e.toString());
   }
}
