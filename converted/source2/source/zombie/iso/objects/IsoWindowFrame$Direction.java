package zombie.iso.objects;

enum IsoWindowFrame$Direction {
   INVALID,
   NORTH,
   WEST;

   public boolean isValid() {
      return this != INVALID;
   }
}
