package zombie.iso;

import java.util.ArrayList;

final class BentFences$Entry {
   IsoDirections dir = IsoDirections.Max;
   final ArrayList<String> unbent = new ArrayList<>();
   final ArrayList<String> bent = new ArrayList<>();

   private BentFences$Entry() {
   }

   boolean isNorth() {
      return this.dir == IsoDirections.N || this.dir == IsoDirections.S;
   }
}
