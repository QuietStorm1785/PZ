package zombie.characters;

public class IsoGameCharacter$Location {
   public int x;
   public int y;
   public int z;

   public IsoGameCharacter$Location() {
   }

   public IsoGameCharacter$Location(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

   public IsoGameCharacter$Location set(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      return this;
   }

   public int getX() {
      return this.x;
   }

   public int getY() {
      return this.y;
   }

   public int getZ() {
      return this.z;
   }

   @Override
   public boolean equals(Object var1) {
      return !(var1 instanceof IsoGameCharacter$Location var2) ? false : this.x == var2.x && this.y == var2.y && this.z == var2.z;
   }
}
